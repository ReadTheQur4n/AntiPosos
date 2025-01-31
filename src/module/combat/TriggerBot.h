#ifndef ANTIPOSOS_TRIGGERBOT_H
#define ANTIPOSOS_TRIGGERBOT_H

#include "../Module.h"

class TriggerBot: public Module {
public:
	int aps = 10;
	float distance = 5.0f;
private:
	int tick = 0;
public:
	TriggerBot();

	void onTick(Level*) override;
};

#endif //ANTIPOSOS_TRIGGERBOT_H
