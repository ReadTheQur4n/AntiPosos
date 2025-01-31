#ifndef ANTIPOSOS_LEVEL_H
#define ANTIPOSOS_LEVEL_H

#include <iostream>
#include "Actor.h"
#include "Block.h"

struct BlockPos;
class WeakStorageEntity;
class Player;

struct HitResult {
	enum Type: int {
		BLOCK = 0,
		ACTOR,
		IDK_LOL,
		AIR
	};
	vec3_t head_pos;
	vec3_t some_shit; // idk what is that
	Type type;
	int side;
	BlockPos block_pos;
	vec3_t view_dir;
	WeakStorageEntity actor;

	Actor* getActor();
};

class Level {
public:
	uintptr_t** vtable;
public:
	std::vector<WeakStorageEntity>& getActiveUsers();
	std::vector<Actor*> getRuntimeActorList();
	HitResult* getHitResult();

	Actor* fetchActor(uint64_t, bool = false);

	void forEachPlayer(std::function<void(Player*)> const&);
	void forEachActor(std::function<void(Actor*)> const&);
};

#endif //ANTIPOSOS_LEVEL_H
