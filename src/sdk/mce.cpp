#include "mce.h"
#include "../memory/offsets.h"

namespace mce {
	glm::mat4& Camera::getViewMatrix() {
		return *(glm::mat4*) ((uintptr_t) this + MCE_CAMERA_VIEW_MATRIX_OFF);
	}
}
