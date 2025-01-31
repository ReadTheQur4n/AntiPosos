#include "Player.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

Player* Player::tryGetFromEntity(uintptr_t entity_context, bool idk) {
	static auto call = (Player*(*) (uintptr_t, bool)) (game.base_addr + PLAYER_TRY_GET_FROM_ENTITY);
	return call(entity_context, idk);
}

GameMode* Player::getGameMode() {
	return *(GameMode**) ((uintptr_t) this + PLAYER_GAME_MODE_OFF);
}

PlayerInventory* Player::getSupplies() {
	return *(PlayerInventory**) ((uintptr_t) this + PLAYER_PLAYER_INVENTORY_OFF);
}

bool Player::isBot() {
	auto hitbox = getComponents()->AABB_shape->size;
	return getNameTag()->empty() || hitbox.x < 0.6f || hitbox.y < 1.5f; // TODO: Other checks
}