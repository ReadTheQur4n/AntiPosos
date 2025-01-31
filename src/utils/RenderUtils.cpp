#include "RenderUtils.h"
#include "../memory/Game.h"

bool RenderUtils::worldToScreen(glm::mat4& v, vec3_t p, vec2_t& screen_coords) {
	p -= vec3_t(v[3][0], v[3][1], v[3][2]);
	/* ALTERNATIVE
	if (!game.getLocalPlayer())
		return false;
	auto origin = game.getLocalPlayer()->getInterpolatedPosition(game.partial_ticks);
	p -= TO_GLM3(origin);
	 */

	float x = p.x * v[0][0] + p.y * v[0][1] + p.z * v[0][2] + v[0][3];
	float y = p.x * v[1][0] + p.y * v[1][1] + p.z * v[1][2] + v[1][3];
	float z = p.x * v[2][0] + p.y * v[2][1] + p.z * v[2][2] + v[2][3];

	float mX = game.screen_size.x / 2.0f;
	float mY = game.screen_size.y / 2.0f;
	float fovX = std::tan(game.fov.x * 0.5f * DEG_RAD) * (game.screen_size.x / game.screen_size.y);
	float fovY = std::tan(game.fov.y * 0.5f * DEG_RAD) * (game.screen_size.x / game.screen_size.y);

	screen_coords.x = mX + (x / -z) * (mX / fovX);
	screen_coords.y = mY - (y / -z) * (mY / fovY);
	return z < 0.0f;
}