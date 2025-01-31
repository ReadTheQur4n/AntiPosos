#include "MainButton.h"
#include "Menu.h"
#include <imgui.h>

MainButton::MainButton(): FloatingButton({ 400, 0 }, { 250, 100 }) {
	toggle();
}

void MainButton::draw() {
	static const char* text = "Menu";
	auto draw_list = ImGui::GetForegroundDrawList();
	draw_list->AddRectFilled(pos.as_imgui(), (pos + size).as_imgui(), IM_COL32(0, 0, 0, 150), 10.0f, 0);
	draw_list->AddText((pos + (size - ImGui::CalcTextSize(text)) / 2).as_imgui(), IM_COL32(255, 255, 255, 255), text, nullptr);
};

void MainButton::onClick() {
	menu.toggle();
}