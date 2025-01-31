#ifndef ANTIPOSOS_KILLAURA_H
#define ANTIPOSOS_KILLAURA_H

#include "../Module.h"

class KillAura: public Module {
public:
	int aps = 5;
	float distance = 3.3f;
	bool multi = false;
private:
	int tick = 0;
public:
	KillAura();

	void onTick(Level*) override;
};


#endif //ANTIPOSOS_KILLAURA_H
