#ifndef ANTIPOSOS_BLOCKFLY_H
#define ANTIPOSOS_BLOCKFLY_H

#include "../Module.h"

struct BlockFlyAmigo {
	BlockPos pos;
	int side;

	BlockFlyAmigo(BlockPos const& pos, int side): pos(pos), side(side) {};
};

class BlockFly: public Module {
private:
	bool auto_select = false;
	int prev_slot = 0;
	std::array<vec3_t, 6> list {
			vec3_t( 0, -1,  0),
			vec3_t( 0,  1,  0),
			vec3_t( 0,  0, -1),
			vec3_t( 0,  0,  1),
			vec3_t(-1,  0,  0),
			vec3_t( 1,  0,  0)
	};
	std::array<vec3_t, 4> angles_extra_check {
			vec3_t(-1, 0, -1),
			vec3_t(-1, 0,  1),
			vec3_t( 1, 0,  1),
			vec3_t( 1, 0, -1)
	};
public:
	BlockFly();

	void onTick(Level*) override;
	void onEnable() override;
	void onDisable() override;
private:
	BlockFlyAmigo getNeighbor(BlockPos const&);
	bool selectSlot();
};


#endif //ANTIPOSOS_BLOCKFLY_H
