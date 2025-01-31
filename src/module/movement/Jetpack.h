#ifndef ANTIPOSOS_JETPACK_H
#define ANTIPOSOS_JETPACK_H

#include "../Module.h"

class Jetpack: public Module {
private:
	float speed = 0.8f;
public:
	Jetpack();

	void onDisable() override;
	void onTick(Level*) override;
};


#endif //ANTIPOSOS_JETPACK_H
