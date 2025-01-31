#include "TraceLines.h"
#include "../../utils/RenderUtils.h"
#include "../../memory/Game.h"
#include <imgui.h>

TraceLines::TraceLines(): Module("TraceLines", Category::RENDER) {
	addSetting<ColorSetting>("Color", &color);
}

void TraceLines::onDrawImGui() {
	if (game.getScreenName() != "hud_screen")
		return;
	game.forEachPlayer([this] (Player* p) {
		if (p == game.getLocalPlayer() || p->isBot())
			return;
		vec2_t screen;
		if (!RenderUtils::worldToScreen(game.camera->getViewMatrix(), p->getInterpolatedPosition(game.partial_ticks), screen))
			screen = game.screen_size - screen;
		ImGui::GetBackgroundDrawList()->AddLine((game.screen_size / 2).as_imgui(), screen.as_imgui(), color.to_imcolor(), 2.0f);
	});
}