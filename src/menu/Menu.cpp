#include "Menu.h"

#include <android/log.h>
#include <android/input.h>
#include <imgui_impl_android.h>
#include <imgui.h>
#include <string>

#include "../utils/Utils.h"
#include "../utils/RenderUtils.h"
#include "../module/ModuleManager.h"
#include "../module/Module.h"
#include "../memory/Game.h"
#include "../memory/Hooks.h"
#include "imgui_internal.h"
#include "Font.h"
#include "NotificationManager.h"

#include "MainButton.h"
#include "elements/ModuleShortcutButton.h"

Menu menu;

void Menu::init() {
	menu.main_button = new MainButton();
	auto& modules = module_manager.getModules();
	for (auto module: modules) {
		auto shortcut = module->getShortcut();
		if (shortcut)
			menu.module_shortcuts.push_back(shortcut);
	}
	menu.font32 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font_raw_data, sizeof(font_raw_data), 32.0f);
	menu.font48 = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(font_raw_data, sizeof(font_raw_data), 48.0f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.0f;
	style.IndentSpacing = 5.0f;
	style.ItemSpacing.x = style.ItemSpacing.y;
	//style.WindowBorderSize = 0.0f;
	//style.WindowPadding = { 2.5f, 2.5f };
	//style.ItemSpacing = { 2.5f, 2.5f };
}

bool Menu::isShowing() const {
	return showing;
}

bool Menu::toggle() {
	return showing = !showing;
}

void Menu::render() {
	notification_manager.render();
	for (auto shortcut: module_shortcuts)
		if (shortcut->isShowing())
			shortcut->draw();
	// Draws main button after shortcuts so that it is always on top
	if (main_button && main_button->isShowing())
		main_button->draw();
	if (showing) {
		ImGui::Begin("AntiPosos", nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize);
		ImGui::Checkbox("Debug info", &draw_debug_info);
		auto& modules = module_manager.getModules();
		for (int i = 0; i < modules.size(); ++i) {
			auto module = modules[i];
			bool toggleable = module->isToggleable();
			if (toggleable)
				ImGui::PushStyleColor(ImGuiCol_Text, module->isEnabled() ? ImVec4(0, 1, 0, 1) : ImVec4(1, 0, 0, 1));
			if (ImGui::Button(module->getName().c_str(), { 300, 0 })) {
				if (toggleable)
					module->toggle();
				else
					module->onClick();
			}
			if (toggleable)
				ImGui::PopStyleColor();
			if (module->getShortcut() || !module->getSettings().empty()) {
				ImGui::SameLine();
				ImGui::PushID(0xDeadBeef + i);
				if (ImGui::Button(module->isSettingsShowing() ? "-" : "+", { 50, 0 }))
					module->toggleSettings();
				ImGui::PopID();
			}
			if (module->isSettingsShowing()) {
				auto shortcut = module->getShortcut();
				if (shortcut) {
					ImGui::PushID(0x1337 + i);
					bool temp = shortcut->isShowing();
					if (ImGui::Checkbox("Shortcut", &temp))
						shortcut->toggle();
					ImGui::PopID();
				}
				auto& settings = module->getSettings();
				for (int j = 0; j < settings.size(); ++j) {
					auto setting = settings[j];
					switch (setting->getType()) {
						case SettingType::BOOL: {
							auto s = (BoolSetting*) setting;
							bool temp = s->isEnabled();
							if (ImGui::Checkbox(s->getName().c_str(), &temp))
								s->toggle();
							break;
						}
						case SettingType::INT: {
							auto s = (IntSetting*) setting;
							int temp = s->getValue();
							ImGui::PushID(0x1488 + i * j);
							ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
							if (ImGui::SliderInt("", &temp, s->getMin(), s->getMax(), s->getFormat().c_str()))
								s->setValue(temp);
							ImGui::PopItemWidth();
							ImGui::PopID();
							break;
						}
						case SettingType::FLOAT: {
							auto s = (FloatSetting*) setting;
							float temp = s->getValue();
							ImGui::PushID(0x1488 + i * j);
							ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x);
							if (ImGui::SliderFloat("", &temp, s->getMin(), s->getMax(), s->getFormat().c_str()))
								s->setValue(temp);
							ImGui::PopItemWidth();
							ImGui::PopID();
							break;
						}
						case SettingType::COLOR: {
							auto s = (ColorSetting*) setting;
							vec4_t temp = s->getColor();
							ImGui::PushID(0x1488 + i * j);
							if (ImGui::ColorEdit4(s->getName().c_str(), (float*) &temp, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar))
								s->setColor(temp);
							ImGui::PopID();
							break;
						}
						/*case SettingType::ENUM: {

							break;
						}
						case SettingType::TEXT: {

							break;
						}*/
					}
				}
			}
		}
		ImGui::End();
	}
	if (draw_debug_info) {
		std::string list;
		list.append(Utils::stringFormat("%ifps, %.4fms", game.fps, 1000.0f / (float) game.fps)).append("\n");
		list.append(Utils::stringFormat("libminecraftpe.so: 0x%lx", game.base_addr)).append("\n");
		if (game.client_instance) {
			/*auto level = game.client_instance->getLevel();
			auto boi = game.getLocalPlayer();
			list.append(Utils::stringFormat("ClientInstance: 0x%lx", game.client_instance)).append("\n");
			list.append(Utils::stringFormat("Level: 0x%lx", level)).append("\n");
			list.append(Utils::stringFormat("LocalPlayer: 0x%lx", boi)).append("\n");
			if (boi) {
				list.append(Utils::stringFormat("\tname_tag: %s", boi->getNameTag()->c_str())).append("\n");
				list.append(Utils::stringFormat("\tunique_id: %i", boi->getUniqueID())).append("\n");
				list.append(Utils::stringFormat("\truntime_id: %i", boi->getRuntimeID())).append("\n");
				list.append(Utils::stringFormat("\tpos: %s", boi->getPos().to_string().c_str())).append("\n");
				list.append(Utils::stringFormat("\trot: %s", boi->getRot().to_string().c_str())).append("\n");
				list.append(Utils::stringFormat("\tcarried_item: 0x%lx", boi->getCarriedItem())).append("\n");
				list.append(Utils::stringFormat("\toffhand_slot: 0x%lx", boi->getOffhandSlot())).append("\n");
				list.append("\tarmor:").append("\n"); {
					list.append(Utils::stringFormat("\t\thelmet: 0x%lx", boi->getArmor(ArmorSlot::HELMET))).append("\n");
					list.append(Utils::stringFormat("\t\tchestplate: 0x%lx", boi->getArmor(ArmorSlot::CHESTPLATE))).append("\n");
					list.append(Utils::stringFormat("\t\tleggings: 0x%lx", boi->getArmor(ArmorSlot::LEGGINGS))).append("\n");
					list.append(Utils::stringFormat("\t\tboots: 0x%lx", boi->getArmor(ArmorSlot::BOOTS))).append("\n");
				}
			}
			if (level) {
				auto hr = level->getHitResult();
				auto amogus = hr->getActor();
				list.append(Utils::stringFormat("HitResult: 0x%lx", hr)).append("\n");
				list.append(Utils::stringFormat("\thead_pos: %s", hr->head_pos.to_string().c_str())).append("\n");
				list.append(Utils::stringFormat("\ttype: %i", hr->type)).append("\n");
				list.append(Utils::stringFormat("\tside: %i", hr->side)).append("\n");
				list.append(Utils::stringFormat("\tblock_pos: [%i, %i, %i]", PASTE_V3(hr->block_pos))).append("\n");
				list.append(Utils::stringFormat("\tview_dir: %s", hr->view_dir.to_string().c_str())).append("\n");
				list.append(Utils::stringFormat("\tactor: 0x%lx", amogus)).append("\n");
				if (amogus) {
					list.append(Utils::stringFormat("\tname_tag: %s", amogus->getNameTag()->c_str())).append("\n");
					list.append(Utils::stringFormat("\tunique_id: %i", amogus->getUniqueID())).append("\n");
					list.append(Utils::stringFormat("\truntime_id: %i", amogus->getRuntimeID())).append("\n");
					list.append(Utils::stringFormat("\tpos: %s", amogus->getPos().to_string().c_str())).append("\n");
					list.append(Utils::stringFormat("\trot: %s", amogus->getRot().to_string().c_str())).append("\n");
					list.append(Utils::stringFormat("\tcarried_item: 0x%lx", amogus->getCarriedItem())).append("\n");
					list.append(Utils::stringFormat("\toffhand_slot: 0x%lx", amogus->getOffhandSlot())).append("\n");
					list.append("\tarmor:").append("\n"); {
						list.append(Utils::stringFormat("\t\thelmet: 0x%lx", amogus->getArmor(ArmorSlot::HELMET))).append("\n");
						list.append(Utils::stringFormat("\t\tchestplate: 0x%lx", amogus->getArmor(ArmorSlot::CHESTPLATE))).append("\n");
						list.append(Utils::stringFormat("\t\tleggings: 0x%lx", amogus->getArmor(ArmorSlot::LEGGINGS))).append("\n");
						list.append(Utils::stringFormat("\t\tboots: 0x%lx", amogus->getArmor(ArmorSlot::BOOTS))).append("\n");
					}
				}
			}*/
		}
		ImGui::GetBackgroundDrawList()->AddText(ImVec2(10.0f, 20.0f), IM_COL32(255, 255, 255, 255), list.c_str());
	}
}

void Menu::handleInputEvent(AInputEvent* event) { // TODO: External keyboard capture for shortcuts & etc
	if (main_button && main_button->isShowing() && main_button->handleInputEvent(event)) { // Buttons have higher priority
		hooks.preventDefault();
		return;
	}
	for (auto it = module_shortcuts.rbegin(); it != module_shortcuts.rend(); ++it) {
		auto shortcut = *it;
		if (shortcut->isShowing() && shortcut->handleInputEvent(event)) {
			// All this is necessary for the correct rendering of shortcuts and the correct input handling in accordance with the "layer" on which the shortcut is drawn
			if (it != module_shortcuts.rend()) {
				module_shortcuts.erase(--it.base());
				module_shortcuts.push_back(shortcut);
			}
			hooks.preventDefault();
			return;
		}
	}
	ImGui_ImplAndroid_HandleInputEvent(event);
	if (!menu.isShowing())
		return;
	int32_t event_type = AInputEvent_getType(event);
	if (event_type == AINPUT_EVENT_TYPE_MOTION) {
		int32_t event_action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
		int32_t event_pointer_index = (event_action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		vec2_t pos {
			AMotionEvent_getX(event, event_pointer_index),
			AMotionEvent_getY(event, event_pointer_index)
		};
		if (event_action == AMOTION_EVENT_ACTION_DOWN && GImGui)
			for (ImGuiWindow* window: GImGui->Windows)
				if (window->Active && pos > window->Pos && pos < window->Pos + window->Size)
					hooks.preventDefault();
	}
}