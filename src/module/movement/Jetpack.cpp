#include "Jetpack.h"
#include "../../utils/Math.h"

Jetpack::Jetpack(): Module("Jetpack", Category::MOVEMENT) {
	addSetting<FloatSetting>("Speed", &speed, 0.0f, 5.0f, "%.2f");
}

void Jetpack::onDisable() {
	auto boi = game.getLocalPlayer();
	if (boi)
		boi->getComponents()->state_vector->velocity = 0.0f;
}

void Jetpack::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;

	auto rot = boi->getRot().addY(90.0f) * DEG_RAD;
	boi->getComponents()->state_vector->velocity = vec3_t(
			cos(rot.y) * cos(rot.x),
			-sin(rot.x),
			sin(rot.y) * cos(rot.x)
	) * speed;
}