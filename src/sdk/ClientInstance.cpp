#include "ClientInstance.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

LocalPlayer* ClientInstance::getLocalPlayer() {
	auto call = (LocalPlayer*(*) (ClientInstance*)) vtable[CLIENT_INSTANCE_GET_LOCAL_PLAYER_VT];
	return call(this);
}

MinecraftGame* ClientInstance::getMinecraftGame() {
	return *(MinecraftGame**) ((uintptr_t) this + CLIENT_INSTANCE_MINECRAFT_GAME_OFF);
}

std::string ClientInstance::getTopScreenName() {
	auto call = (std::string(*) (ClientInstance*)) vtable[CLIENT_INSTANCE_GET_TOP_SCREEN_NAME_VT];
	return call(this);
}

Minecraft* ClientInstance::getServerData() {
	return *(Minecraft**) ((uintptr_t) this + CLIENT_INSTANCE_MINECRAFT_OFF);
}

Level* ClientInstance::getLevel() {
	auto call = (Level*(*) (ClientInstance*)) vtable[CLIENT_INSTANCE_GET_LEVEL_VT];
	return call(this);
}

LoopbackPacketSender* ClientInstance::getPacketSender() {
	return *(LoopbackPacketSender**) ((uintptr_t) this + CLIENT_INSTANCE_PACKET_SENDER_OFF);
}

MoveInputHandler* ClientInstance::getMoveTurnInput() {
	static auto call = (MoveInputHandler*(*) (ClientInstance*)) (game.base_addr + CLIENT_INSTANCE_GET_MOVE_TURN_INPUT);
	return call(this);
}