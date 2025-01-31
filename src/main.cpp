#include <jni.h>
#include <android/native_activity.h>
#include <dlfcn.h>

#include "memory/Game.h"
#include "memory/Hooks.h"
#include "module/ModuleManager.h"
#include "utils/Utils.h"

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* jvm, void*) {
	game.jvm = jvm;
	game.base_addr = Utils::findLibrary("libminecraftpe.so");
	Hooks::init(game.base_addr);
	ModuleManager::init();
	return JNI_VERSION_1_6;
}