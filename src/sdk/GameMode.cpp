#include "GameMode.h"
#include "../memory/offsets.h"

void GameMode::startBuildBlock(BlockPos const& pos, uint8_t side) {
	auto call = (void(*) (GameMode*, BlockPos const&, uint8_t)) vtable[GAME_MODE_START_BUILD_BLOCK_VT];
	call(this, pos, side);
}

void GameMode::buildBlock(BlockPos const& pos, uint8_t side, bool idk) {
	auto call = (void(*) (GameMode*, BlockPos const&, uint8_t, bool)) vtable[GAME_MODE_BUILD_BLOCK_VT];
	call(this, pos, side, idk);
}

void GameMode::continueBuildBlock(BlockPos const& pos, uint8_t side) {
	auto call = (void(*) (GameMode*, BlockPos const&, uint8_t)) vtable[GAME_MODE_CONTINUE_BUILD_BLOCK_VT];
	call(this, pos, side);
}

void GameMode::stopBuildBlock() {
	auto call = (void(*) (GameMode*)) vtable[GAME_MODE_STOP_BUILD_BLOCK_VT];
	call(this);
}

// Actually just sends an InventoryTransactionPacket, so if you call that only, you may be detected by AntiCheat
void GameMode::attack(Actor* actor) {
	auto call = (void(*) (GameMode*, Actor*)) vtable[GAME_MODE_ATTACK_VT];
	call(this, actor);
}

void GameMode::placeBlock(BlockPos const& pos, uint8_t side) {
	startBuildBlock(pos, side);
	continueBuildBlock(pos, side);
	buildBlock(pos, side, false);
	stopBuildBlock();
}