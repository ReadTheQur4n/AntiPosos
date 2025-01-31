#ifndef ANTIPOSOS_AIMBOT_H
#define ANTIPOSOS_AIMBOT_H

#include "../Module.h"

class AimBot: public Module {
private:
	//bool mobs = false;
	float distance = 7.0f;
public:
	AimBot();

	void onTick(Level*) override;
};

#endif //ANTIPOSOS_AIMBOT_H
