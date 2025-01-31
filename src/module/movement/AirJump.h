#ifndef ANTIPOSOS_AIRJUMP_H
#define ANTIPOSOS_AIRJUMP_H

#include "../Module.h"

class AirJump: public Module {
private:
	bool jump_button_pressed = false;
public:
	AirJump();

	void onTick(Level*) override;
};

#endif //ANTIPOSOS_AIRJUMP_H
