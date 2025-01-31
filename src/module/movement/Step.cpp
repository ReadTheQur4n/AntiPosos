#include "Step.h"

Step::Step(): Module("Step", Category::MOVEMENT) {
	addSetting<FloatSetting>("Height", &height, 0.0f, 2.0f, "%.2f");
}

void Step::onDisable() {
	auto boi = game.getLocalPlayer();
	if (boi)
		boi->setStepHeight(0.5625f);
}

void Step::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (boi)
		boi->setStepHeight(height);
}