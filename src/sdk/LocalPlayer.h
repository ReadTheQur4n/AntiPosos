#ifndef ANTIPOSOS_LOCALPLAYER_H
#define ANTIPOSOS_LOCALPLAYER_H

#include "Player.h"

class LocalPlayer: public Player {
public:
	void swing();
	void attack(Actor*);
	void setRot(vec2_t const&);
};

#endif //ANTIPOSOS_LOCALPLAYER_H
