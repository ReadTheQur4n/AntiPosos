#include "Inventory.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

int Item::getId() {
	return *(uint16_t*) ((uintptr_t) this + ITEM_ID_OFF);
}

int Item::getMaxUseDuration() {
	return *(int*) ((uintptr_t) this + ITEM_MAX_USE_DURATION_OFF);
}

void Item::setMaxUseDuration(int duration) {
	*(int*) ((uintptr_t) this + ITEM_MAX_USE_DURATION_OFF) = duration;
}

Item* ItemStackBase::getItem() {
	uintptr_t /* ItemRegistryRef* */ ref = *(uintptr_t*) ((uintptr_t) this + ITEM_STACK_BASE_ITEM_REGISTRY_REF_OFF);
	if (ref)
		return *(Item**) ref;
	return nullptr;
}

Block* ItemStackBase::getBlock() {
	return *(Block**) ((uintptr_t) this + ITEM_STACK_BASE_BLOCK_OFF);
}

int ItemStackBase::getId() {
	return !isNull() ? getItem()->getId() : 0;
}

int ItemStackBase::getAuxValue() {
	static auto call = (uint16_t(*) (ItemStackBase*)) (game.base_addr + ITEM_STACK_BASE_GET_AUX_VALUE);
	return call(this);
}

bool ItemStackBase::isNull() {
	static auto call = (bool(*) (ItemStackBase*)) (game.base_addr + ITEM_STACK_BASE_IS_NULL);
	return call(this);
}

bool ItemStackBase::isWearableItem() {
	static auto call = (bool(*) (ItemStackBase*)) (game.base_addr + ITEM_STACK_BASE_IS_WEARABLE_ITEM);
	return call(this);
}

int ItemStackBase::getArmorSlot() {
	// ArmorItem::getSlotForItem returns 0 if the item is not wearable, it may confuse
	if (!isWearableItem())
		return -1;
	static auto call = (uint8_t(*) (ItemStackBase*)) (game.base_addr + ARMOR_ITEM_GET_SLOT_FOR_ITEM);
	return call(this);
}

int ItemStackBase::getMaxUseDuration() {
	return !isNull() ? getItem()->getMaxUseDuration() : 0;
}

void ItemStackBase::setMaxUseDuration(int duration) {
	if (!isNull())
		getItem()->setMaxUseDuration(duration);
}

ItemStack* PlayerInventory::getItem(int slot, ContainerID container_id) {
	static auto call = (ItemStack*(*) (PlayerInventory*, int, ContainerID)) (game.base_addr + PLAYER_INVENTORY_GET_ITEM);
	return call(this, slot, container_id);
}

ItemStack* PlayerInventory::getSelectedItem() {
	static auto call = (ItemStack*(*) (PlayerInventory*)) (game.base_addr + PLAYER_INVENTORY_GET_SELECTED_ITEM);
	return call(this);
}

int PlayerInventory::getSelectedSlot() {
	static auto call = (uint64_t(*) (PlayerInventory*)) (game.base_addr + PLAYER_INVENTORY_GET_SELECTED_SLOT);
	return (int) (call(this) >> 32);
}

void PlayerInventory::selectSlot(int slot, bool is_inventory) {
	static auto call = (void(*) (PlayerInventory*, int, bool)) (game.base_addr + PLAYER_INVENTORY_SELECT_SLOT);
	call(this, slot, is_inventory);
}
