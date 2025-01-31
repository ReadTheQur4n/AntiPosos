#include "FloatingButton.h"
#include "../../memory/Game.h"
#include "../../utils/Utils.h"
#include <vector>

FloatingButton::FloatingButton(vec2_t const& pos, vec2_t const& size) {
	this->pos = pos;
	this->size = size;
}

bool FloatingButton::isShowing() const {
	return showing;
}

vec2_t FloatingButton::getPos() const {
	return pos;
}

vec2_t FloatingButton::getSize() const {
	return size;
}

bool FloatingButton::isIntersects(vec2_t const& p) const {
	return pos < p && p < (pos + size);
}

void FloatingButton::toggle() {
	showing = !showing;
}

void FloatingButton::move(vec2_t const& p) {
	// anti idiot
	pos = p;
	if (pos.x < 0)
		pos.x = 0;
	if (pos.y < 0)
		pos.y = 0;
	if (pos.x + size.x > game.screen_size.x)
		pos.x = game.screen_size.x - size.x;
	if (pos.y + size.y > game.screen_size.y)
		pos.y = game.screen_size.y - size.y;
}

void FloatingButton::moveX(float x) {
	pos.x = x;
	if (pos.x < 0)
		pos.x = 0;
	if (pos.x + size.x > game.screen_size.x)
		pos.x = game.screen_size.x - size.x;
}

void FloatingButton::moveY(float y) {
	pos.y = y;
	if (pos.y < 0)
		pos.y = 0;
	if (pos.y + size.y > game.screen_size.y)
		pos.y = game.screen_size.y - size.y;
}

bool FloatingButton::handleInputEvent(AInputEvent* event) {
	int32_t type = AInputEvent_getType(event);
	if (type == AINPUT_EVENT_TYPE_MOTION) {
		int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
		int32_t pointer_index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT; // Action pointer index
		size_t pointer_count = AMotionEvent_getPointerCount(event); // usually max=10 for ching chong touch screen
		for (size_t i = 0; i < pointer_count; i++) {
			int pointer_id = AMotionEvent_getPointerId(event, i);
			vec2_t pointer_pos {
					AMotionEvent_getX(event, i),
					AMotionEvent_getY(event, i)
			};
			switch (action) {
				case AMOTION_EVENT_ACTION_POINTER_DOWN:
				case AMOTION_EVENT_ACTION_DOWN: {
					if (drag.moving && pointer_count != 1)
						return true; // prevents from clicking on screen while dragging
					if (!drag.moving && isIntersects(pointer_pos)) {
						drag.pointer_index = pointer_id;
						drag.clicked = true;
						drag.start_pos = pointer_pos;
						return true;
					}
					break;
				}
				case AMOTION_EVENT_ACTION_POINTER_UP:
				case AMOTION_EVENT_ACTION_UP: {
					if (drag.moving && pointer_count != 1)
						return true;
					if (drag.pointer_index == pointer_id) {
						if (drag.clicked && isIntersects(pointer_pos))
							onClick();
						drag.pointer_index = -1;
						drag.start_pos = 0.0f;
						drag.moving_delta = 0.0f;
						drag.moving = false;
						drag.clicked = false;
						return true;
					}
					break;
				}
				case AMOTION_EVENT_ACTION_MOVE: {
					if (pointer_count == 1 && drag.pointer_index == pointer_id) { // prevent from moving while 2+ clicks
						if (!drag.moving)
							drag.moving_delta = drag.start_pos - pointer_pos;
						if (drag.moving || drag.moving_delta.magnitude() > SAFE_ZONE) {
							drag.clicked = false;
							drag.moving = true;
							move(pointer_pos - size / 2);
						}
					}
					break;
				}
				default:
					break;
			}
		}
	}
	return false;
}
