#ifndef ANTIPOSOS_STEP_H
#define ANTIPOSOS_STEP_H

#include "../Module.h"

class Step: public Module {
private:
	float height = 2.0f;
public:
	Step();

	void onDisable() override;
	void onTick(Level*) override;
};

#endif //ANTIPOSOS_STEP_H
