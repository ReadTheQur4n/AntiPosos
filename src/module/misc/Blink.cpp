#include "Blink.h"
#include "../../memory/Hooks.h"

Blink::Blink(): Module("Blink", Category::MISC) {}

Blink::~Blink() {
	Module::~Module();
	if (!packets.empty())
		for (Packet* packet: packets)
			delete packet;
	packets.clear();
}

void Blink::onDisable() {
	Level* level = game.client_instance->getLevel();
	if (!level)
		goto end;
	if (!packets.empty())
		for (Packet* packet: packets) {
			game.client_instance->getPacketSender()->send(packet);
			delete packet;
		}
end:
	packets.clear();
}

void Blink::onSendPacket(Packet* packet) {
	if (packet->getId() == PacketId::MOVE_PLAYER_PACKET) {
		auto pkt = (MovePlayerPacket*) malloc(sizeof(MovePlayerPacket));
		memcpy(pkt, packet, sizeof(MovePlayerPacket));
		pkt->on_ground = true;
		packets.push_back(pkt);
		hooks.preventDefault();
	} else if (packet->getId() == PacketId::PLAYER_AUTH_INPUT_PACKET) {
		auto pkt = (PlayerAuthInputPacket*) malloc(sizeof(PlayerAuthInputPacket));
		memcpy(pkt, packet, sizeof(PlayerAuthInputPacket));
		packets.push_back(pkt);
		hooks.preventDefault();
	}
}