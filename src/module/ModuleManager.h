#ifndef ANTIPOSOS_MODULEMANAGER_H
#define ANTIPOSOS_MODULEMANAGER_H

#include <iostream>
#include <vector>
#include <functional>

#include "Module.h"

#define INVOKE_MODULE_CALLBACK(NAME, ...) for (Module* module: modules) if (module->isEnabled()) module->NAME(__VA_ARGS__);

class ModuleManager {
private:
	std::vector<Module*> modules;
public:
	~ModuleManager();

	static void init();

	std::vector<Module*>& getModules();
	template <typename T> T* getModule() {
		for (Module* module: modules)
			if (dynamic_cast<T*>(module) != nullptr)
				return (T*) module;
		return nullptr;
	};

	void onDrawImGui();
	void onTick(Level*);
	void onSendPacket(Packet*);
	void onReceivePacket(Packet*);

	void load(json&);
	void save(json&);
};

extern ModuleManager module_manager;

#endif //ANTIPOSOS_MODULEMANAGER_H
