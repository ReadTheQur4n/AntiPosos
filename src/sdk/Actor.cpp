#include "Actor.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

StackResultStorageEntity::StackResultStorageEntity(WeakStorageEntity& storage) {
	static auto call = (StackResultStorageEntity*(*) (StackResultStorageEntity*, WeakStorageEntity&)) (game.base_addr + STACK_RESULT_STORAGE_ENTITY_CONSTRUCTOR);
	call(this, storage);
}

bool StackResultStorageEntity::_hasValue() {
	static auto call = (bool(*) (StackResultStorageEntity*)) (game.base_addr + STACK_RESULT_STORAGE_ENTITY__HAS_VALUE);
	return call(this);
}

uintptr_t StackResultStorageEntity::_getStackRef() {
	static auto call = (uintptr_t(*) (StackResultStorageEntity*)) (game.base_addr + STACK_RESULT_STORAGE_ENTITY__GET_STACK_REF);
	return call(this);
}

std::string* SynchedActorDataEntityWrapper::getString(int index) {
	static auto call = (std::string*(*) (SynchedActorDataEntityWrapper*, int)) (game.base_addr + SYNCHED_ACTOR_DATA_ENTITY_WRAPPER_GET_STRING);
	return call(this, index);
}

bool SynchedActorDataEntityWrapper::getStatusFlag(ActorFlag flag) {
	static auto call = (bool(*) (SynchedActorDataEntityWrapper*, ActorFlag)) (game.base_addr + SYNCHED_ACTOR_DATA_ENTITY_WRAPPER_GET_STATUS_FLAG);
	return call(this, flag);
}

void SynchedActorDataEntityWrapper::setStatusFlag(ActorFlag flag, bool status) {
	static auto call = (bool(*) (SynchedActorDataEntityWrapper*, int, bool)) (game.base_addr + SYNCHED_ACTOR_DATA_ENTITY_WRAPPER_SET_STATUS_FLAG);
	call(this, flag, status);
}

Actor* Actor::tryGetFromEntity(uintptr_t entity_context, bool idk) {
	static auto call = (Actor*(*) (uintptr_t, bool)) (game.base_addr + ACTOR_TRY_GET_FROM_ENTITY);
	return call(entity_context, idk);
}

SynchedActorDataEntityWrapper* Actor::getEntityData(bool first) {
	return (SynchedActorDataEntityWrapper*) ((uintptr_t) this + (first ? ACTOR_FIRST_SYNCHED_ACTOR_DATA_ENTITY_WRAPPER_OFF : ACTOR_SECOND_SYNCHED_ACTOR_DATA_ENTITY_WRAPPER_OFF));
}

BuiltInActorComponents* Actor::getComponents() {
	return (BuiltInActorComponents*) ((uintptr_t) this + ACTOR_BUILT_IN_ACTOR_COMPONENTS_OFF);
}

vec3_t Actor::getInterpolatedPosition(float partial) {
	return getPrevPos().lerp(getPos(), partial);
}

vec3_t Actor::getPos() {
	return getComponents()->state_vector->pos;
}

vec3_t Actor::getPrevPos() {
	return getComponents()->state_vector->prev_pos;
}

vec3_t Actor::getVel() {
	return getComponents()->state_vector->velocity;
}

vec2_t Actor::getRot() {
	return getComponents()->actor_rotation->rot;
}

vec2_t Actor::getPrevRot() {
	return getComponents()->actor_rotation->prev_rot;
}

void Actor::setPos(vec3_t const& pos) {
	static auto call = (void(*) (Actor*, vec3_t const&)) (game.base_addr + ACTOR_SET_POS);
	call(this, pos);
}

std::string* Actor::getNameTag() {
	return getEntityData(false)->getString(4);
}

Dimension* Actor::getDimension() {
	static auto call = (Dimension*(*) (Actor*)) (game.base_addr + ACTOR_GET_DIMENSION);
	return call(this);
};

uint64_t Actor::getUniqueID() {
	static auto call = (uint64_t*(*) (Actor*)) (game.base_addr + ACTOR_GET_UNIQUE_ID);
	return *call(this);
}

uint64_t Actor::getRuntimeID() {
	static auto call = (uint64_t(*) (Actor*)) (game.base_addr + ACTOR_GET_RUNTIME_ID);
	return call(this);
}

bool Actor::getStatusFlag(ActorFlag flag) {
	return getEntityData(true)->getStatusFlag(flag);
}

void Actor::setStatusFlag(ActorFlag flag, bool status) {
	getEntityData(true)->setStatusFlag(flag, status);
}

BlockSource* Actor::getRegion() {
	return getDimension()->getBlockSourceFromMainChunkSource();
}

float Actor::getDistanceTo(Actor* actor) {
	return getPos().distance(actor->getPos());
}

float Actor::getDistanceTo(vec3_t const& pos) {
	return getPos().distance(pos);
}

unsigned int Actor::getEntityTypeId() {
	static auto call = (unsigned int(*) (Actor*)) (game.base_addr + ACTOR_GET_ENTITY_TYPE_ID);
	return call(this);
}

void Actor::setStepHeight(float height) {
	static auto call = (void(*) (Actor*, float)) (game.base_addr + ACTOR__INITIALIZE_MAX_AUTO_STEP);
	call(this, height);
}

ItemStack* Actor::getCarriedItem() {
	auto call = (ItemStack*(*) (Actor*)) vtable[ACTOR_GET_CARRIED_ITEM_VT];
	return call(this);
}

ItemStack* Actor::getOffhandSlot() {
	static auto call = (ItemStack*(*) (Actor*)) (game.base_addr + ACTOR_GET_OFFHAND_SLOT);
	return call(this);
}

ItemStack* Actor::getArmor(ArmorSlot slot) {
	static auto call = (ItemStack*(*) (Actor*, ArmorSlot)) (game.base_addr + ACTOR_GET_ARMOR);
	return call(this, slot);
}

bool Actor::isOnGround() {
	static auto call = (bool(*) (uintptr_t)) (game.base_addr + ACTOR_COLLISION_IS_ON_GROUND);
	return call((uintptr_t) this + ACTOR_ACTOR_COLLISION_OFF);
}