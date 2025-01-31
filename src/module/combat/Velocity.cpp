#include "Velocity.h"
#include "../../memory/Hooks.h"

Velocity::Velocity(): Module("Velocity", Category::COMBAT) {
	addSetting<FloatSetting>("Horizontal", &amplifier.x, 0.0f, 1.0f, "%.2f");
	addSetting<FloatSetting>("Vertical", &amplifier.y, 0.0f, 1.0f, "%.2f");
}

void Velocity::onReceivePacket(Packet* packet) {
	if (packet->getId() == PacketId::SET_ACTOR_MOTION_PACKET) {
		auto pkt = (SetActorMotionPacket*) packet;
		if (amplifier == 0.0f) {
			hooks.preventDefault();
			return;
		}
		pkt->motion.x *= amplifier.x;
		pkt->motion.y *= amplifier.y;
		pkt->motion.z *= amplifier.x;
	}
}
