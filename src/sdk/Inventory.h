#ifndef ANTIPOSOS_INVENTORY_H
#define ANTIPOSOS_INVENTORY_H

#include <iostream>

class Block;

enum ContainerID: uint8_t {
	INVENTORY = 0,
	FIRST = 1,
	LAST = 100,
	OFFHAND = 119,
	ARMOR = 120,
	HOT_BAR = 122,
	FIXED_INVENTORY = 123,
	UI = 124,
	CONTAINER_ID_REGISTRY = 125,
	NONE = 255
};

enum ArmorSlot: uint8_t {
	HELMET = 0,
	CHESTPLATE,
	LEGGINGS,
	BOOTS
};

class Item {
public:
	uintptr_t** vtable;
public:
	int getId();
	int getMaxUseDuration();
	void setMaxUseDuration(int);
};

class ItemStackBase {
public:
	Item* getItem();
	Block* getBlock();
	int getId();
	int getAuxValue();
	bool isNull();
	bool isWearableItem();
	int getArmorSlot();
	int getMaxUseDuration(); // This method is implemented in ItemStack, but I don't care, I am the boss here
	void setMaxUseDuration(int);
};

class ItemStack: public ItemStackBase {
public:

};

class PlayerInventory {
public:
	ItemStack* getItem(int, ContainerID = ContainerID::INVENTORY);
	ItemStack* getSelectedItem();
	void selectSlot(int, bool = true);
	int getSelectedSlot();
};

#endif //ANTIPOSOS_INVENTORY_H
