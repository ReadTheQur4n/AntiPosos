#ifndef ANTIPOSOS_HOOKS_H
#define ANTIPOSOS_HOOKS_H

#include <memory>
#include <jni.h>
#include <android/native_activity.h>
#include <EGL/egl.h>
#include <GLES2/gl2.h>
#include <functional>

#include "Dobby.h"
#include "../sdk/sdk.h"

#define DECL_HOOK(NAME, RET, ...) static RET NAME(__VA_ARGS__); std::unique_ptr<Hook> NAME##_hook
#define HOOK(NAME, ADDRESS) hooks.NAME##_hook = std::make_unique<Hook>((void*) (ADDRESS), (void*) Hooks::NAME)
#define HOOKED(NAME) hooks.NAME##_hook
#define GET_ORIGINAL(NAME, RET, ...) hooks.NAME##_hook->getOriginal<RET, __VA_ARGS__>()

class Hook {
private:
	void* original = nullptr;
public:
	Hook(void* address, void* hook) {
		DobbyHook(address, hook, &original);
	}
	Hook(uintptr_t address, void* hook) {
		DobbyHook(reinterpret_cast<void*>(address), hook, &original);
	}

	template <typename T_ret, typename... T_args>
	inline auto* getOriginal() {
		return reinterpret_cast<T_ret(*)(T_args...)>(original);
	}
};

class Hooks {
public:
	bool prevent_default_status = false;
	std::array<std::shared_ptr<Hook>, PacketId::END - 1> packet_handlers;
public:
	static void init(uintptr_t);
public:
	void preventDefault();
private:
	DECL_HOOK(handle_input, void, AInputEvent*);
	DECL_HOOK(ClientInstance_update, bool, ClientInstance*, bool);
	DECL_HOOK(LevelRendererPlayer_getFov, float, uintptr_t, char, float);
	DECL_HOOK(ContainerScreenController_tick, uintptr_t, ContainerScreenController*);
	DECL_HOOK(eglSwapBuffers, EGLBoolean, EGLDisplay, EGLSurface);
	//DECL_HOOK(input, void, AInputEvent*, void*, void*);
	DECL_HOOK(Level_tick, void, Level*);
	DECL_HOOK(LoopbackPacketSender_send, uintptr_t, LoopbackPacketSender*, Packet*);
	DECL_HOOK(MinecraftGame_update, uintptr_t, MinecraftGame*);
	DECL_HOOK(MinecraftGame_onAppResumed, uintptr_t, MinecraftGame*);
	DECL_HOOK(Actor_isInvisible, bool, Actor*);
private:
	static uintptr_t PacketHandlerDispatcherInstance_handle(uintptr_t, uintptr_t, uintptr_t, std::shared_ptr<Packet>&);
};

extern Hooks hooks;

#endif //ANTIPOSOS_HOOKS_H
