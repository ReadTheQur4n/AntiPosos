#ifndef ANTIPOSOS_CHESTSTEALER_H
#define ANTIPOSOS_CHESTSTEALER_H

#include "../Module.h"

class ChestStealer: public Module {
public:
	int loot_delay = 1;
	int close_delay = 2;

	int loot_tick;
	int close_tick;
public:
	ChestStealer();
};

#endif //ANTIPOSOS_CHESTSTEALER_H
