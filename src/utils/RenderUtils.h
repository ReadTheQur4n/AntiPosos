#ifndef ANTIPOSOS_RENDERUTILS_H
#define ANTIPOSOS_RENDERUTILS_H

#include <mat4x4.hpp>
#include <vec3.hpp>
#include "Math.h"

namespace RenderUtils {
	bool worldToScreen(glm::mat4&, vec3_t, vec2_t&);
};

#endif //ANTIPOSOS_RENDERUTILS_H
