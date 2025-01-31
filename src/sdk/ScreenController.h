#ifndef ANTIPOSOS_SCREENCONTROLLER_H
#define ANTIPOSOS_SCREENCONTROLLER_H

#include <iostream>

class ItemStack;

class MinecraftScreenController/*: public ScreenController*/ {
public:
	uintptr_t** vtable;
public:
	void tryExit();
};

class ContainerScreenController: public MinecraftScreenController {
public:
	ItemStack* _getItemStack(std::string const&, int);
	void _handleAutoPlace(int, std::string const&, int);
};

#endif //ANTIPOSOS_SCREENCONTROLLER_H
