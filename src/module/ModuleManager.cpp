#include "ModuleManager.h"

#include "../config/ConfigManager.h"

#include "combat/AimBot.h"
#include "combat/KillAura.h"
#include "combat/TriggerBot.h"
#include "combat/Velocity.h"
#include "misc/Blink.h"
#include "misc/Configs.h"
#include "misc/ChestStealer.h"
#include "misc/NoInvisible.h"
#include "movement/AirJump.h"
#include "movement/BlockFly.h"
#include "movement/Jetpack.h"
#include "movement/Step.h"
#include "render/NameTags.h"
#include "render/TraceLines.h"

ModuleManager module_manager;

ModuleManager::~ModuleManager() {
	for (Module* module: modules)
		delete module;
}

void ModuleManager::init() {
	module_manager.modules = {
			new Configs(),
			new AimBot(),
			new KillAura(),
			new TriggerBot(),
			new Velocity(),
			new Blink(),
			new ChestStealer(),
			new NoInvisible(),
			new AirJump(),
			new Jetpack(),
			new BlockFly(),
			new Step(),
			new NameTags(),
			new TraceLines(),
	};
}

std::vector<Module*>& ModuleManager::getModules() {
	return modules;
}

void ModuleManager::onDrawImGui() {
	INVOKE_MODULE_CALLBACK(onDrawImGui);
}

void ModuleManager::onTick(Level* level) {
	INVOKE_MODULE_CALLBACK(onTick, level);
}

void ModuleManager::onSendPacket(Packet* packet) {
	INVOKE_MODULE_CALLBACK(onSendPacket, packet);
}

void ModuleManager::onReceivePacket(Packet* packet) {
	INVOKE_MODULE_CALLBACK(onReceivePacket, packet);
}

void ModuleManager::load(json& config) {
	for (Module* module: modules)
		if (config.contains(module->getName())) {
			json& module_config = config[module->getName()];
			module->load(module_config);
		}
}

void ModuleManager::save(json& config) {
	for (Module* module: modules)
		module->save(config);
}