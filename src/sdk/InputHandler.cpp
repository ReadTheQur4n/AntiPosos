#include "InputHandler.h"
#include "../memory/offsets.h"

bool MoveInputHandler::isJumpDown() const {
	return *(bool*) (this + MOVE_INPUT_HANDLER_JUMP_DOWN_OFF);
}