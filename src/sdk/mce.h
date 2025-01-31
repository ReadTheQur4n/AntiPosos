#ifndef ANTIPOSOS_MCE_H
#define ANTIPOSOS_MCE_H

#include <mat4x4.hpp>
#include "../memory/offsets.h"

namespace mce {
	enum PrimitiveMode: int {
		NONE = 0,
		QUAD_LIST = 1,
		TRIANGLE_LIST = 2,
		TRIANGLE_STRIP = 3,
		LINE_LIST = 4,
		LINE_STRIP = 5,
	};
	class Camera {
	public:
		glm::mat4& getViewMatrix();
	};
}

#endif
