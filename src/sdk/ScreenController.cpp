#include "ScreenController.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

void MinecraftScreenController::tryExit() {
	auto call = (void(*) (MinecraftScreenController*)) vtable[MINECRAFT_SCREEN_CONTROLLER_TRY_EXIT_VT];
	call(this);
}

ItemStack* ContainerScreenController::_getItemStack(std::string const& id /* container id from which item will be taken */, int slot) {
	auto call = (ItemStack*(*) (ContainerScreenController*, std::string const&, int)) (game.base_addr + CONTAINER_SCREEN_CONTROLLER__GET_ITEM_STACK);
	return call(this, id, slot);
}

void ContainerScreenController::_handleAutoPlace(int idk, std::string const& id /* same shit as in ContainerScreenController::_getItemStack */, int slot) {
	static auto call = (void(*) (ContainerScreenController*, int, std::string const&, int)) (game.base_addr + CONTAINER_SCREEN_CONTROLLER__HANDLE_AUTO_PLACE);
	call(this, idk, id, slot);
}