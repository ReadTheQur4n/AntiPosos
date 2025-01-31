#ifndef ANTIPOSOS_GAMEMODE_H
#define ANTIPOSOS_GAMEMODE_H

#include <iostream>

struct BlockPos;
struct vec3_t;
class Actor;

class GameMode {
public:
	uintptr_t** vtable;
public:
	void startBuildBlock(BlockPos const&, uint8_t);
	void buildBlock(BlockPos const&, uint8_t, bool);
	void continueBuildBlock(BlockPos const&, uint8_t);
	void stopBuildBlock();
	void attack(Actor*);

	void placeBlock(BlockPos const&, uint8_t);
};

#endif //ANTIPOSOS_GAMEMODE_H
