#include "NameTags.h"
#include "../../utils/RenderUtils.h"
#include "../../memory/Game.h"
#include <imgui.h>

NameTags::NameTags(): Module("NameTags", Category::RENDER) {
	addSetting<ColorSetting>("Color", &color);
}

void NameTags::onDrawImGui() {
	if (game.getScreenName() != "hud_screen")
		return;
	game.forEachPlayer([this] (Player* p) {
		if (p == game.getLocalPlayer() || p->isBot())
			return;
		vec2_t screen;
		if (RenderUtils::worldToScreen(game.camera->getViewMatrix(), p->getInterpolatedPosition(game.partial_ticks).addY(0.62f), screen)) {
			auto s = Utils::trim(purifyName(p->getNameTag()->c_str()));
			auto d = ImGui::GetBackgroundDrawList();
			auto size = ImGui::CalcTextSize(s.c_str());
			auto pos = screen - size / 2.0f;
			d->AddRectFilled(pos.sub(10.0f).as_imgui(), pos.add(size).add(10.0f).as_imgui(), IM_COL32(0, 0, 0, 150), 10.0f, 0);
			d->AddText(pos.as_imgui(), color.to_imcolor(), s.c_str(), nullptr);
		}
	});
}

std::string NameTags::purifyName(std::string const& name) {
	std::string result;
	for (size_t i = 0; i < name.size(); ++i) {
		if ((unsigned char) name[i] == 0xC2) {
			i += 2;
			continue;
		}
		if (isalnum((unsigned char) name[i]))
			result += name[i];
	}
	return result;
}