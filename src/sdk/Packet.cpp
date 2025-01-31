#include "Packet.h"
#include "Actor.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

void LoopbackPacketSender::send(Packet* packet) {
	auto call = (uintptr_t(*) (LoopbackPacketSender*, Packet*)) vtable[LOOPBACK_PACKET_SENDER_SEND_VT];
	call(this, packet);
}

PacketId Packet::getId() {
	auto call = (PacketId(*) (Packet*)) vtable[PACKET_GET_ID_VT];
	return call(this);
}

std::string Packet::getName() {
	auto call = (std::string(*) (Packet*)) vtable[PACKET_GET_NAME_VT];
	return call(this);
}

// MinecraftPackets::createPacket sounds cringe, so I created this method in the Packet class
std::shared_ptr<Packet> Packet::create(PacketId id) {
	static auto call = (std::shared_ptr<Packet>(*) (PacketId)) (game.base_addr + MINECRAFT_PACKETS_CREATE_PACKET);
	return call(id);
}