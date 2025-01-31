#include "Game.h"

Game game;

std::string Game::getScreenName() const {
	if (!client_instance)
		return "";
	return client_instance->getTopScreenName();
}

LocalPlayer* Game::getLocalPlayer() const {
	if (!client_instance)
		return nullptr;
	return client_instance->getLocalPlayer();
}

AppPlatform* Game::getAppPlatform() const {
	return *(AppPlatform**) ((*(uintptr_t*) (base_addr + SOME_SHIT_THAT_CONTAINS_APP_PLATFORM_OFF)) + 8);
}

void Game::forEachPlayer(std::function<void(Player*)> const& callback) const {
	if (!client_instance)
		return;
	Level* level = client_instance->getLevel();
	if (!level)
		return;
	level->forEachPlayer(callback);
}

void Game::forEachActor(std::function<void(Actor*)> const& callback) const {
	if (!client_instance)
		return;
	Level* level = client_instance->getLevel();
	if (!level)
		return;
	level->forEachActor(callback);
}