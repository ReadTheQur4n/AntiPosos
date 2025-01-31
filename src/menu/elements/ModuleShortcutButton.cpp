#include "ModuleShortcutButton.h"

#include "../../module/Module.h"

ModuleShortcutButton::ModuleShortcutButton(Module* module): FloatingButton({ 50, 50 }, { 120, 120 }) {
	this->module = module;
}

void ModuleShortcutButton::draw() {
	if (!module)
		return;
	const char* text = module->getName().c_str();
	auto draw_list = ImGui::GetForegroundDrawList();
	draw_list->AddRectFilled(pos.as_imgui(), (pos + size).as_imgui(), IM_COL32(0, 0, 0, 150), 10.0f, 0);
	draw_list->AddText((pos + (size - ImGui::CalcTextSize(text)) / 2).as_imgui(), module->isEnabled() ? IM_COL32(0, 255, 0, 255) : IM_COL32(255, 0, 0, 255), text, nullptr);
};

void ModuleShortcutButton::onClick() {
	if (!module)
		return;
	module->toggle();
}