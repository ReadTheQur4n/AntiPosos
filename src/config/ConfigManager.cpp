#include "ConfigManager.h"

#include <filesystem>
#include <sstream>
#include <fstream>

#include "../module/ModuleManager.h"

ConfigManager config_manager;

ConfigManager::ConfigManager() {
	std::filesystem::create_directories(getConfigsFolder());
}

std::string ConfigManager::getConfigsFolder() {
	return "/data/data/" + Utils::getPackageName() + "/configs/";
}

std::string ConfigManager::getSelectedConfigName() {
	return selected_config_name;
}

bool ConfigManager::load(std::string const& name) {
	std::string path = getConfigsFolder() + name + ".json";
	bool exists = std::filesystem::exists(path);
	if (exists) {
		json config;
		selected_config_name = name;
		std::ifstream file(path, std::ios::binary);
		if (file.is_open()) {
			file >> config;
			file.close();
		}
		{
			module_manager.load(config);
		}
	}
	return exists;
}

bool ConfigManager::save(std::string const& name) {
	std::string path = getConfigsFolder() + name + ".json";
	bool saved = false;
	json config;
	selected_config_name = name;
	{
		module_manager.save(config);
	}
	std::ofstream file(path, std::ios::binary);
	if (file.is_open()) {
		file << config;
		file.close();
		saved = true;
	}
	return saved;
}

bool ConfigManager::remove(std::string const& name) {
	std::string path = getConfigsFolder() + name + ".json";
	bool removed = false;
	if (std::filesystem::exists(path)) {
		if (selected_config_name == name)
			selected_config_name.clear();
		std::filesystem::remove(path);
		removed = true;
	}
	return removed;
}

std::string ConfigManager::importFromString(std::string const& string) {
	std::string result;
	if (string.empty() || string.rfind("AntiPososConfig_", 0) != 0)
		return result;
	json config = json::parse(Utils::b64d(string.substr(16)));
	if (!config.contains("name") || !config.contains("content"))
		return result;
	if (config["name"].is_string() && config["content"].is_object()) {
		std::string name = config["name"].get<std::string>();
		json& content = config["content"];
		std::string path = getConfigsFolder() + name + ".json";
		std::ofstream file(path);
		if (!file.is_open())
			return result;
		result = name;
		file << content;
		file.close();
	}
	return result;
}

bool ConfigManager::exportToClipboard(std::string const& name) {
	std::string path = getConfigsFolder() + name + ".json";
	bool exists = std::filesystem::exists(path);
	if (exists) {
		json content;
		std::ifstream file(path, std::ios::binary);
		if (file.is_open()) {
			file >> content;
			file.close();
		}
		std::stringstream stream;
		stream << json {
			{ "name", name },
			{ "content", content }
		};
		game.getAppPlatform()->setClipboardText("AntiPososConfig_" + Utils::b64e(stream.str()));
	}
	return exists;
}