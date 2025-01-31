#include "BlockFly.h"

BlockFly::BlockFly(): Module("BlockFly", Category::MOVEMENT) {
	addSetting<BoolSetting>("Auto select block", &auto_select);
	//addSetting<BoolSetting>("Tower", &tower);
	//addSetting<IntSetting>("Blocks predict", &blocks_predict, 0, 12, "%i"); // do it yourself skidder, clue: ray trace forward
}

void BlockFly::onEnable() {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;
	if (auto_select) {
		prev_slot = boi->getSupplies()->getSelectedSlot();
		selectSlot();
	}
}

void BlockFly::onDisable() {
	auto boi = game.getLocalPlayer();
	if (!boi)
		return;
	if (auto_select && prev_slot != -1)
		boi->getSupplies()->selectSlot(prev_slot);
	prev_slot = -1;
}

void BlockFly::onTick(Level* level) {
	auto boi = game.getLocalPlayer();
	if (!boi || !boi->getGameMode() || !selectSlot())
		return;
	vec3_t pos = boi->getPos().subY(2.0f).add(boi->getVel());
	pos = { floor(pos.x), floor(pos.y), floor(pos.z) };
	auto faggot = getNeighbor(pos);
	if (faggot.side != -1)
		boi->getGameMode()->placeBlock(faggot.pos, faggot.side);
}

BlockFlyAmigo BlockFly::getNeighbor(BlockPos const& pos) {
	BlockFlyAmigo null({ 0, 0, 0 }, -1);
	auto boi = game.getLocalPlayer();
	auto r = boi->getRegion();
	if (!r)
		return null;
	auto b = r->getBlock(pos);
	if (!b)
		return null;
	auto m = b->getMaterial();
	if (!m)
		return null;
	if (m->solid)
		return null;

	for (int i = 0; i < list.size(); i++) {
		vec3_t n = vec3_t(pos.x, pos.y, pos.z) - list[i];
		b = r->getBlock(n);
		if (!b)
			continue;
		m = b->getMaterial();
		if (!m)
			continue;
		if (m->solid)
			return { n, i };
	}
	for (int i = 0; i < angles_extra_check.size(); i++) {
		vec3_t n = vec3_t(pos.x, pos.y, pos.z) - angles_extra_check[i];
		b = r->getBlock(n);
		if (!b)
			continue;
		m = b->getMaterial();
		if (!m)
			continue;
		if (m->solid)
			return { n, i + 2 };
	}
	return null;
}

bool BlockFly::selectSlot() {
	auto boi = game.getLocalPlayer();
	auto s = boi->getSupplies();
	if (!auto_select || boi->getCarriedItem()->getBlock())
		return true;
	else {
		int flex_slot = -1;
		for (int i = 0; i < 9; i++) {
			auto item = s->getItem(i);
			if (item->getBlock()) {
				flex_slot = i;
				break;
			}
		}
		if (flex_slot != -1) {
			s->selectSlot(flex_slot);
			return true;
		}
	}
	return false;
}