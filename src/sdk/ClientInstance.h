#ifndef ANTIPOSOS_CLIENTINSTANCE_H
#define ANTIPOSOS_CLIENTINSTANCE_H

#include <cstdint>
#include <string>

class Level;
class LocalPlayer;
class Minecraft;
class MinecraftGame;
class LoopbackPacketSender;
class MoveInputHandler;

class ClientInstance {
public:
	uintptr_t** vtable;
public:
	LocalPlayer* getLocalPlayer();
	MinecraftGame* getMinecraftGame();
	std::string getTopScreenName();
	Minecraft* getServerData();
	Level* getLevel();
	LoopbackPacketSender* getPacketSender();
	MoveInputHandler* getMoveTurnInput();
};

#endif //ANTIPOSOS_CLIENTINSTANCE_H
