#include "AirJump.h"

AirJump::AirJump(): Module("AirJump", Category::MOVEMENT) {}

void AirJump::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	auto handler = game.client_instance->getMoveTurnInput();
	if (boi->isOnGround())
		jump_button_pressed = true;
	else {
		if (handler->isJumpDown() && !jump_button_pressed) {
			jump_button_pressed = true;
			boi->getComponents()->state_vector->velocity.y = 0.42f;
		}
		if (!handler->isJumpDown())
			jump_button_pressed = false;
	}
}