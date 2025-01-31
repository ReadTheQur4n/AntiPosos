#include "AimBot.h"

AimBot::AimBot(): Module("AimBot", Category::COMBAT) {
	addSetting<FloatSetting>("Distance", &distance, 0.0f, 10.0f, "%.2f");
}

void AimBot::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;
	Player* nearest = nullptr;
	float nearest_distance = distance;
	level->forEachPlayer([&boi, &nearest, &nearest_distance] (Player* p) {
		if (p != boi && boi->getDistanceTo(p) < nearest_distance && !p->isBot()) {
			nearest_distance = boi->getDistanceTo(p);
			nearest = p;
		}
	});
	if (nearest)
		boi->setRot(boi->getPos().angle(nearest->getPos().subY(0.5f)));
}