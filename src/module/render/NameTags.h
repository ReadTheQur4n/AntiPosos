#ifndef ANTIPOSOS_NAMETAGS_H
#define ANTIPOSOS_NAMETAGS_H

#include "../Module.h"
#include "../../utils/Math.h"

class NameTags: public Module {
private:
	vec4_t color = 1.0f;
public:
	NameTags();

	void onDrawImGui() override;
private:
	std::string purifyName(std::string const& name);
};


#endif
