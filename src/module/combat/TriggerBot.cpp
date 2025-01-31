#include "TriggerBot.h"
#include "../../memory/Game.h"

TriggerBot::TriggerBot(): Module("TriggerBot", Category::COMBAT) {
	addSetting<IntSetting>("APS", &aps, 1, 20);
	addSetting<FloatSetting>("Distance", &distance, 0.0f, 10.0f, "%.2f");
}

void TriggerBot::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;

	tick++;
	if ((float) tick >= 20.0f / (float) aps) {
		auto actor = level->getHitResult()->getActor();
		if (actor && boi->getDistanceTo(actor) <= distance)
			boi->attack(actor);
		tick = 0;
	}
}