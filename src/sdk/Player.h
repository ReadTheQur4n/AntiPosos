#ifndef ANTIPOSOS_PLAYER_H
#define ANTIPOSOS_PLAYER_H

#include "Actor.h"

class GameMode;
class PlayerInventory;

class Player: public Actor {
public:
	static Player* tryGetFromEntity(uintptr_t /* EntityContext& */, bool);
public:
	GameMode* getGameMode();
	PlayerInventory* getSupplies();

	bool isBot();
};

#endif //ANTIPOSOS_PLAYER_H
