#include "Level.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

Actor* HitResult::getActor() {
	StackResultStorageEntity stack_result(actor);
	if (stack_result._hasValue())
		return Actor::tryGetFromEntity(stack_result._getStackRef(), true);
	return nullptr;
}

std::vector<WeakStorageEntity>& Level::getActiveUsers() {
	auto call = (std::vector<WeakStorageEntity>&(*) (Level*)) vtable[LEVEL_GET_ACTIVE_USERS_VT];
	return call(this);
}

std::vector<Actor*> Level::getRuntimeActorList() {
	auto call = (std::vector<Actor*>(*) (Level*)) vtable[LEVEL_GET_RUNTIME_ACTOR_LIST_VT];
	return call(this);
}

HitResult* Level::getHitResult() {
	auto call = (HitResult*(*) (Level*)) vtable[LEVEL_GET_HIT_RESULT_VT];
	return call(this);
}

Actor* Level::fetchActor(uint64_t id, bool runtime) {
	std::vector<Actor*> actors = getRuntimeActorList();
	for (Actor* actor: actors)
		if ((runtime ? actor->getRuntimeID() : actor->getUniqueID()) == id)
			return actor;
	return nullptr;
}

void Level::forEachPlayer(std::function<void(Player*)> const& callback) {
	std::vector<WeakStorageEntity>& users = getActiveUsers();
	for (WeakStorageEntity& user: users) {
		StackResultStorageEntity stack_result(user);
		if (stack_result._hasValue()) {
			Player* player = Player::tryGetFromEntity(stack_result._getStackRef(), true);
			if (player)
				callback(player);
		}
	}
}

void Level::forEachActor(std::function<void(Actor*)> const& callback) {
	std::vector<Actor*> actors = getRuntimeActorList();
	for (Actor* actor: actors)
		callback(actor);
}