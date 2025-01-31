#include "Configs.h"
#include "../ModuleManager.h"
#include "../../config/ConfigManager.h"
#include "../../menu/NotificationManager.h"

#include <sstream>

Configs::Configs(): Module("Configs", Category::MISC, true, false) {
	updateList();
}

bool config_name_getter(void* data, int index, const char** output) {
	static auto module = module_manager.getModule<Configs>();
	*output = ((std::string*) data)[index].c_str();
	return true;
}

std::string generate_config_name() {
	std::time_t temp = time(nullptr);
	std::tm* t = std::gmtime(&temp);
	std::stringstream stream;
	stream << std::put_time(t, "%Y-%m-%d %I:%M:%S %p");
	return stream.str();
}

void Configs::onDrawImGui() {
	ImGuiStyle& style = ImGui::GetStyle();
	ImGui::SetNextWindowPos(((game.screen_size - window_size) / 2.0f).as_imgui());
	ImGui::Begin(getName().c_str(), nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
	ImVec2 avail = ImGui::GetContentRegionAvail();
	ImGui::PushItemWidth(avail.x);
	ImGui::Text("Config list (%li)", config_list.size());
	ImGui::Text("Selected: %s", config_manager.getSelectedConfigName().c_str());
	ImGui::ListBox("##ListBox::ConfigList", &selected_config_index, config_name_getter, config_list.data(), config_list.size());
	ImGui::PopItemWidth();
	if (ImGui::Button("Import", { (avail.x - style.ItemSpacing.x) / 2.0f, 75 })) {
		std::string imported_config_name = config_manager.importFromString(game.getAppPlatform()->getClipboardText());
		notification_manager.add(
				!imported_config_name.empty() ? "Config imported (" + imported_config_name + ")" :
				"Config was not found in the clipboard"
		);
		updateList();
	}
	ImGui::SameLine();
	if (ImGui::Button("Export", { (avail.x - style.ItemSpacing.x) / 2.0f, 75 }))
		notification_manager.add(
				selected_config_index == -1 ? "Choose config" :
				config_manager.exportToClipboard(config_list[selected_config_index]) ? "Exported to clipboard" :
				"Incorrect name"
		);
	if (ImGui::Button("Save", { (avail.x - style.ItemSpacing.x) / 2.0f, 75 })) {
		notification_manager.add(
				config_manager.save(selected_config_index == -1 ? generate_config_name() : config_list[selected_config_index]) ? "Config saved" :
				"Incorrect name"
		);
		updateList();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load", { (avail.x - style.ItemSpacing.x) / 2.0f, 75 }))
		notification_manager.add(
				selected_config_index == -1 ? "Choose config" :
				config_manager.load(config_list[selected_config_index]) ? "Config loaded" :
				"Incorrect name"
		);
	if (ImGui::Button("Remove", { avail.x, 75 })) {
		notification_manager.add(
				selected_config_index == -1 ? "Choose config" :
				config_manager.remove(config_list[selected_config_index]) ? "Config removed" :
				"Incorrect name"
		);
		updateList();
	}
	window_size = ImGui::GetWindowSize();
	ImGui::End();
}

void Configs::updateList() {
	config_list.clear();
	std::vector<std::string> temp;
	auto dir = std::filesystem::directory_iterator(ConfigManager::getConfigsFolder());
	for (auto& entry: dir)
		if (entry.is_regular_file()) {
			std::string name = entry.path().filename().string();
			std::string extension = ".json";
			if (name.size() >= extension.size() && name.compare(name.size() - extension.size(), extension.size(), extension) == 0)
				temp.push_back(entry.path().string());
		}
	std::sort(temp.begin(), temp.end(), [] (std::string const& a, std::string const& b) {
		return std::filesystem::last_write_time(a) > std::filesystem::last_write_time(b);
	});
	for (std::string const& path: temp) {
		size_t pos = path.find_last_of('/') + 1;
		config_list.push_back(path.substr(pos, path.size() - pos - 5));
	}
}