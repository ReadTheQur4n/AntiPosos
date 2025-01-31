#include "ChestStealer.h"

ChestStealer::ChestStealer(): Module("ChestStealer", Category::MISC) {
	addSetting<IntSetting>("Loot delay", &loot_delay, 0, 50, "%i");
	addSetting<IntSetting>("Close delay", &close_delay, 0, 50, "%i");
}