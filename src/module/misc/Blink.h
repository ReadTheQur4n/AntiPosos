#ifndef ANTIPOSOS_BLINK_H
#define ANTIPOSOS_BLINK_H

#include "../Module.h"

class Blink: public Module {
private:
	std::vector<Packet*> packets;
public:
	Blink();
	~Blink() override;

	void onDisable() override;
	void onSendPacket(Packet*) override;
};

#endif //ANTIPOSOS_BLINK_H
