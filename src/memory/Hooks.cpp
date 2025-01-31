#include "Hooks.h"

#include <android/log.h>
#include <dlfcn.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_android.h>

#include "Game.h"
#include "Dobby.h"
#include "offsets.h"

#include "../menu/Menu.h"
#include "../utils/Utils.h"

#include "../module/ModuleManager.h"
#include "../module/misc/ChestStealer.h"
#include "../module/misc/NoInvisible.h"

Hooks hooks;

void Hooks::init(uintptr_t base_addr) {
	HOOK(handle_input, base_addr + HANDLE_INPUT);
	HOOK(ClientInstance_update, base_addr + CLIENT_INSTANCE_UPDATE);
	HOOK(LevelRendererPlayer_getFov, base_addr + LEVEL_RENDERER_PLAYER_GET_FOV);
	HOOK(ContainerScreenController_tick, base_addr + CONTAINER_SCREEN_CONTROLLER_TICK);
	// MinecraftPackets::createPacket which is called in Packet::create returns nullptr if the packet id is incorrect
	// so I just iterate from 0 to PacketId::END and hook its handler if packet with such id exists
	for (int i = 0; i < PacketId::END; ++i) {
		auto packet = Packet::create((PacketId) i);
		if (packet)
			hooks.packet_handlers[i] = std::make_shared<Hook>(CAST_VT(packet->handler)[PACKET_HANDLER_DISPATCHER_INSTANCE_HANDLE_VT], (void*) Hooks::PacketHandlerDispatcherInstance_handle);
	}
}

void Hooks::preventDefault() {
	prevent_default_status = true;
}

void Hooks::handle_input(AInputEvent* event) {
	hooks.prevent_default_status = false;
	menu.handleInputEvent(event);
	if (!hooks.prevent_default_status)
		GET_ORIGINAL(handle_input, void, AInputEvent*)(event); // it does not eats pure 0
}

bool Hooks::ClientInstance_update(ClientInstance* self, bool a2) {
	if (!game.client_instance)
		game.client_instance = self;
	{
		if (!HOOKED(eglSwapBuffers))
			HOOK(eglSwapBuffers, DobbySymbolResolver("/system/lib/libEGL.so", "eglSwapBuffers"));
		/*if (!HOOKED(input))
			HOOK(input, DobbySymbolResolver("/system/lib/libinput.so", "_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"));*/
	}
	{
		if (!HOOKED(Level_tick) && self->getLevel())
			HOOK(Level_tick, self->getLevel()->vtable[LEVEL_TICK_VT]);
		if (!HOOKED(LoopbackPacketSender_send) && self->getPacketSender())
			HOOK(LoopbackPacketSender_send, self->getPacketSender()->vtable[LOOPBACK_PACKET_SENDER_SEND_VT]);
		if (!HOOKED(MinecraftGame_onAppResumed))
			HOOK(MinecraftGame_onAppResumed, self->getMinecraftGame()->vtable[MINECRAFT_GAME_ON_APP_RESUMED_VT]);
		if (!HOOKED(MinecraftGame_update))
			HOOK(MinecraftGame_update, self->getMinecraftGame()->vtable[MINECRAFT_GAME_UPDATE_VT]);
		if (!HOOKED(Actor_isInvisible) && self->getLocalPlayer())
			HOOK(Actor_isInvisible, self->getLocalPlayer()->vtable[ACTOR_IS_INVISIBLE_VT]);
	}
	return GET_ORIGINAL(ClientInstance_update, bool, ClientInstance*, bool)(self, a2);
}

float Hooks::LevelRendererPlayer_getFov(uintptr_t self, char a2, float partial_ticks) {
	float result = GET_ORIGINAL(LevelRendererPlayer_getFov, float, uintptr_t, char, float)(self, a2, partial_ticks);
	if (result != 70.0f)
		game.fov = {
				result,
				(2 * atan(tan(result * DEG_RAD / 2) * game.screen_size.y / game.screen_size.x)) * RAD_DEG
		};
	game.camera = (mce::Camera*) ((uintptr_t) self + LEVEL_RENDERER_PLAYER_MCE_CAMERA_OFF);
	game.partial_ticks = partial_ticks;
	return result;
}

// idk&c how many ticks per second in this shit
uintptr_t Hooks::ContainerScreenController_tick(ContainerScreenController* self) {
	static auto module = module_manager.getModule<ChestStealer>();
	if (module->isEnabled()) {
		std::string screen = game.getScreenName();
		if (screen.find("chest") == std::string::npos && screen.find("hopper") == std::string::npos && screen.find("dropper") == std::string::npos && screen.find("dispenser") == std::string::npos && screen.find("shulker") == std::string::npos)
			return GET_ORIGINAL(ContainerScreenController_tick, uintptr_t, ContainerScreenController*)(self);
		std::vector<int> slots;
		for (int i = 0; i < 54; i++)
			if (!self->_getItemStack("container_items", i)->isNull())
				slots.push_back(i);
		if (!slots.empty()) {
			module->loot_tick++;
			if (module->loot_tick >= module->loot_delay)
				for (int slot: slots) {
					self->_handleAutoPlace(0x7FFFFFFF, "container_items", slot);
					if (module->loot_delay != 0) {
						module->loot_tick = 0;
						break;
					}
				}
		} else {
			module->close_tick++;
			if (module->close_tick >= module->close_delay) {
				self->tryExit();
				module->close_tick = 0;
			}
		}
	}
	return GET_ORIGINAL(ContainerScreenController_tick, uintptr_t, ContainerScreenController*)(self);
}

EGLBoolean Hooks::eglSwapBuffers(EGLDisplay display, EGLSurface surface) {
	static GLint gl_width = 0, gl_height = 0;
	eglQuerySurface(display, surface, EGL_WIDTH, &gl_width);
	eglQuerySurface(display, surface, EGL_HEIGHT, &gl_height);
	game.screen_size = { (float) gl_width, (float) gl_height };

	static bool imgui_setup = false;
	if (!imgui_setup) {
		IMGUI_CHECKVERSION();

		ImGui::CreateContext();
		ImGui::GetIO().DisplaySize = ImVec2((float) gl_width, (float) gl_height);
		ImGui_ImplOpenGL3_Init("#version 100");

		Menu::init();
		ImGui::GetStyle().ScaleAllSizes(3.0f);
		imgui_setup = true;
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	module_manager.onDrawImGui();
	menu.render();
	ImGui::EndFrame();
	ImGui::Render();
	glViewport(0, 0, (int) io.DisplaySize.x, (int) io.DisplaySize.y);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return GET_ORIGINAL(eglSwapBuffers, EGLBoolean, EGLDisplay, EGLSurface)(display, surface);
}

/*void Hooks::input(AInputEvent* self, void* ex_ab, void* ex_ac) {
	GET_ORIGINAL(input, void, AInputEvent*, void*, void*)(self, ex_ab, ex_ac);
	menu.handleInputEvent(self);
}*/

void Hooks::Level_tick(Level* self) {
	module_manager.onTick(self);
	GET_ORIGINAL(Level_tick, void, Level*)(self);
}

uintptr_t Hooks::LoopbackPacketSender_send(LoopbackPacketSender* self, Packet* packet) {
	hooks.prevent_default_status = false;
	module_manager.onSendPacket(packet);
	return hooks.prevent_default_status ? 0 : GET_ORIGINAL(LoopbackPacketSender_send, uintptr_t, LoopbackPacketSender*, Packet*)(self, packet);
}

uintptr_t Hooks::MinecraftGame_onAppResumed(MinecraftGame* self) {
	uintptr_t result = GET_ORIGINAL(MinecraftGame_onAppResumed, uintptr_t, MinecraftGame*)(self);
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplOpenGL3_Init();
	return result;
}

uintptr_t Hooks::MinecraftGame_update(MinecraftGame* self) {
	static int frame_count = 0;
	static uint64_t elapsed_time = 0;
	uint64_t current_time = Utils::getCurrentTimeMs();
	uintptr_t result = GET_ORIGINAL(MinecraftGame_update, uintptr_t, MinecraftGame*)(self);
	frame_count++;
	elapsed_time += Utils::getCurrentTimeMs() - current_time;
	if (elapsed_time >= 1000) {
		game.fps = frame_count - 1;
		frame_count = 0;
		elapsed_time = 0;
	}
	return result;
}

bool Hooks::Actor_isInvisible(Actor* self) {
	static auto module = module_manager.getModule<NoInvisible>();
	return module->isEnabled() ? false : GET_ORIGINAL(Actor_isInvisible, bool, Actor*)(self);
}

uintptr_t Hooks::PacketHandlerDispatcherInstance_handle(uintptr_t self, uintptr_t id, uintptr_t callback, std::shared_ptr<Packet>& packet) {
	hooks.prevent_default_status = false;
	module_manager.onReceivePacket(packet.get());
	return hooks.prevent_default_status ? 0 : hooks.packet_handlers[packet->getId()]->getOriginal<uintptr_t, uintptr_t, uintptr_t, uintptr_t, std::shared_ptr<Packet>&>()(self, id, callback, packet);
}