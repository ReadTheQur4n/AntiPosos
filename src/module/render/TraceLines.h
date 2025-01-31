#ifndef ANTIPOSOS_TRACELINES_H
#define ANTIPOSOS_TRACELINES_H

#include "../Module.h"
#include "../../utils/Math.h"

class TraceLines: public Module {
private:
	vec4_t color = 1.0f;
public:
	TraceLines();

	void onDrawImGui() override;
};

#endif
