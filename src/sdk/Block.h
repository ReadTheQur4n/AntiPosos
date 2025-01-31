#ifndef ANTIPOSOS_BLOCK_H
#define ANTIPOSOS_BLOCK_H

#include <cstdint>
#include "../utils/Math.h"

struct BlockPos {
	int x, y, z;

	BlockPos(): x(0), y(0), z(0) {}
	BlockPos(int x, int y, int z): x(x), y(y), z(z) {}
	BlockPos(float x, float y, float z): x((int) x), y((int) y), z((int) z) {}
	BlockPos(vec3_t const& pos): x((int) pos.x), y((int) pos.y), z((int) pos.z) {}
};

enum MaterialType: int {
	AIR = 0,
	DIRT,
	WOOD ,
	STONE,
	METAL,
	WATER,
	LAVA,
	BED = 12,
	ANY = 54
};
// From AmethystAPI
/*enum MaterialType: unsigned int {
	AIR,
	DIRT,
	WOOD,
	STONE,
	METAL,
	WATER,
	LAVA,
	LEAVES,
	PLANT,
	SOLID_PLANT,
	REPLACEABLE_PLANT,
	SPONGE,
	CLOTH,
	BED,
	FIRE,
	SAND,
	DECORATION,
	GLASS,
	EXPLOSIVE,
	ICE,
	PACKED_ICE,
	TOP_SNOW,
	SNOW,
	POWDER_SNOW,
	AMETHYST,
	CACTUS,
	CLAY,
	VEGETABLE,
	PORTAL,
	CAKE,
	WEB,
	REDSTONE_WIRE,
	CARPET,
	BUILDABLE_GLASS,
	SLIME,
	PISTON,
	ALLOW,
	DENY,
	NETHERWART,
	STONE_DECORATION,
	BUBBLE,
	EGG,
	SOFT_EGG,
	BARRIER,
	CORAL,
	DECORATION_SOLID,
	DRIPSTONE,
	REINFORCED_STONE,
	SCULK,
	SCULK_VEIN,
	CLIENT_REQUEST_PLACEHOLDER,
	STRUCTURE_VOID,
	ROOT,
	ANY
};*/

class Material {
public:
	MaterialType type;
	bool never_buildable;
	bool always_destroyable;
	bool liquid;
	float translucency;
	bool blocks_motion;
	bool blocks_precipitation;
	bool solid;
	bool super_hot;
};

class BlockLegacy {
public:
	Material* getMaterial();
};

class Block {
public:
	BlockLegacy* getLegacy();
	Material* getMaterial();
};

class BlockSource {
public:
	uintptr_t** vtable;
public:
	Block* getBlock(BlockPos const&);
};

#endif //ANTIPOSOS_BLOCK_H
