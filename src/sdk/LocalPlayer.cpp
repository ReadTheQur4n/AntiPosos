#include "LocalPlayer.h"
#include "GameMode.h"

#include "../memory/Game.h"
#include "../memory/offsets.h"

void LocalPlayer::swing() {
	auto call = (void(*) (LocalPlayer*)) vtable[LOCAL_PLAYER_SWING_VT];
	call(this);
}

void LocalPlayer::attack(Actor* actor) {
	swing();
	swing();
	getGameMode()->attack(actor);
}

void LocalPlayer::setRot(vec2_t const& rot) {
	auto call = (void(*) (LocalPlayer*)) vtable[LOCAL_PLAYER_RESET_ROT_VT];
	getComponents()->actor_rotation->rot = rot;
	call(this);
}