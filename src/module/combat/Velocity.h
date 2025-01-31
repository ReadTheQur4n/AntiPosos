#ifndef ANTIPOSOS_VELOCITY_H
#define ANTIPOSOS_VELOCITY_H

#include "../Module.h"

class Velocity: public Module {
public:
	vec2_t amplifier = 0.0f;
public:
	Velocity();

	void onReceivePacket(Packet*) override;
};

#endif //ANTIPOSOS_VELOCITY_H
