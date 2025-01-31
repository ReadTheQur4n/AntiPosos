#ifndef ANTIPOSOS_CONFIGMANAGER_H
#define ANTIPOSOS_CONFIGMANAGER_H

#include "../utils/json.hpp"

using json = nlohmann::json;

class ConfigManager {
private:
	std::string selected_config_name;
public:
	ConfigManager();

	static std::string getConfigsFolder();

	std::string getSelectedConfigName();
	bool load(std::string const&);
	bool save(std::string const&);
	bool remove(std::string const&);
	std::string importFromString(std::string const&);
	bool exportToClipboard(std::string const&);
};

#endif //ANTIPOSOS_CONFIGMANAGER_H

extern ConfigManager config_manager;