#include "Block.h"
#include "../memory/Game.h"
#include "../memory/offsets.h"

Material* BlockLegacy::getMaterial() {
	return *(Material**) ((uintptr_t) this + BLOCK_LEGACY_MATERIAL_OFF);
}

BlockLegacy* Block::getLegacy() {
	return *(BlockLegacy**) ((uintptr_t) this + BLOCK_BLOCK_LEGACY_OFF);
}

Material* Block::getMaterial() {
	auto legacy = getLegacy();
	return legacy ? legacy->getMaterial() : nullptr;
}

Block* BlockSource::getBlock(BlockPos const& pos) {
	auto call = (Block*(*) (BlockSource*, BlockPos const&)) vtable[BLOCK_SOURCE_GET_BLOCK_VT];
	return call(this, pos);
}