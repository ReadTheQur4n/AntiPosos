#include "KillAura.h"
#include "../../memory/Game.h"

KillAura::KillAura(): Module("KillAura", Category::COMBAT) {
	addSetting<IntSetting>("APS", &aps, 1, 20, "%i");
	addSetting<FloatSetting>("Distance", &distance, 0.0f, 10.0f, "%.2f");
	addSetting<BoolSetting>("Multi", &multi);
}

void KillAura::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;

	tick++;
	if ((float) tick >= 20.0f / (float) aps) {
		if (multi)
			level->forEachPlayer([this, &boi] (Player* p) {
				if (p != boi && boi->getDistanceTo(p) < this->distance && !p->isBot())
					boi->attack(p);
			});
		else {
			Player* nearest = nullptr;
			float nearest_distance = distance;
			level->forEachPlayer([&boi, &nearest, &nearest_distance] (Player* p) {
				if (p != boi && boi->getDistanceTo(p) < nearest_distance && !p->isBot()) {
					nearest_distance = boi->getDistanceTo(p);
					nearest = p;
				}
			});
			if (nearest)
				boi->attack(nearest);
		}
		tick = 0;
	}
}