#ifndef ANTIPOSOS_GAME_H
#define ANTIPOSOS_GAME_H

#include <iostream>
#include <jni.h>
#include "../utils/Utils.h"
#include "../sdk/sdk.h"

class Game {
public:
	JavaVM* jvm;
	uintptr_t base_addr;
	ClientInstance* client_instance;
	mce::Camera* camera;
	vec2_t screen_size;
	int fps;
	float partial_ticks;
	vec2_t fov = 70.0f;

	std::string getScreenName() const;
	LocalPlayer* getLocalPlayer() const;
	AppPlatform* getAppPlatform() const;
	void forEachPlayer(std::function<void(Player*)> const&) const;
	void forEachActor(std::function<void(Actor*)> const&) const;
};

extern Game game;

#endif //ANTIPOSOS_GAME_H
