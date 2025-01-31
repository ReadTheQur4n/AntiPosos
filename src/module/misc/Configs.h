#ifndef ANTIPOSOS_CONFIGS_H
#define ANTIPOSOS_CONFIGS_H

#include "../Module.h"

class Configs: public Module {
private:
	vec2_t window_size;
public:
	int selected_config_index = -1;
	std::vector<std::string> config_list;
public:
	Configs();

	void onDrawImGui() override;
public:
	void updateList();
};

#endif //ANTIPOSOS_CONFIGS_H
