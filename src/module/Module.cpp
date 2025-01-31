#include "Module.h"

#include "../menu/elements/ModuleShortcutButton.h"
#include "../menu/NotificationManager.h"

Setting::Setting(std::string const& name, SettingType type) {
	this->name = name;
	this->type = type;
}

std::string Setting::getName() {
	return name;
}

SettingType Setting::getType() {
	return type;
}

BoolSetting::BoolSetting(std::string const& name, bool* enabled, std::function<void(bool)> const& on_toggle_callback): Setting(name, SettingType::BOOL) {
	this->enabled = enabled;
	this->on_toggle_callback = on_toggle_callback;
}

bool BoolSetting::isEnabled() {
	return *enabled;
}

void BoolSetting::setEnabled(bool enabled) {
	*this->enabled = enabled;
}

void BoolSetting::toggle() {
	*enabled = !*enabled;
	if (on_toggle_callback)
		on_toggle_callback(*enabled);
}

void BoolSetting::load(json& config) {
	if (config.is_boolean() && *enabled != config.get<bool>())
		toggle();
}

void BoolSetting::save(json& config) {
	config.emplace(getName(), *enabled);
}

IntSetting::IntSetting(std::string const& name, int* value, int min, int max, std::string const& format, std::function<void(int)> const& on_value_change_callback): Setting(name, SettingType::INT) {
	this->value = value;
	this->min = min;
	this->max = max;
	this->format = name + ": " + format;
	this->on_value_change_callback = on_value_change_callback;
}

void IntSetting::setValue(int value) {
	*this->value = value;
	if (on_value_change_callback)
		on_value_change_callback(value);
}

int IntSetting::getValue() {
	return *value;
}

int IntSetting::getMin() const {
	return min;
}

int IntSetting::getMax() const {
	return max;
}

std::string IntSetting::getFormat() const {
	return format;
}

void IntSetting::load(json& config) {
	if (config.is_number_integer())
		setValue(std::min(std::max(config.get<int>(), min), max));
}

void IntSetting::save(json& config) {
	config.emplace(getName(), *value);
}

FloatSetting::FloatSetting(std::string const& name, float* value, float min, float max, std::string const& format, std::function<void(float)> const& on_value_change_callback): Setting(name, SettingType::FLOAT) {
	this->value = value;
	this->min = min;
	this->max = max;
	this->format = name + ": " + format;
	this->on_value_change_callback = on_value_change_callback;
}

void FloatSetting::setValue(float value) {
	*this->value = value;
	if (on_value_change_callback)
		on_value_change_callback(value);
}

float FloatSetting::getValue() {
	return *value;
}

float FloatSetting::getMin() const {
	return min;
}

float FloatSetting::getMax() const {
	return max;
}

std::string FloatSetting::getFormat() const {
	return format;
}

void FloatSetting::load(json& config) {
	if (config.is_number_float())
		setValue(std::min(std::max(config.get<float>(), min), max));
}

void FloatSetting::save(json& config) {
	config.emplace(getName(), *value);
}

ColorSetting::ColorSetting(std::string const& name, vec4_t* color): Setting(name, SettingType::COLOR) {
	this->color = color;
}

void ColorSetting::setColor(vec4_t const& color) {
	*this->color = color;
}

vec4_t ColorSetting::getColor() {
	return *color;
}

void ColorSetting::load(json& config) {
	if (!config.is_object())
		return;
	if (config.contains("red") && config["red"].is_number_float())
		color->r = std::min(std::max(config["red"].get<float>(), 0.0f), 1.0f);
	if (config.contains("green") && config["green"].is_number_float())
		color->g = std::min(std::max(config["green"].get<float>(), 0.0f), 1.0f);
	if (config.contains("blue") && config["blue"].is_number_float())
		color->b = std::min(std::max(config["blue"].get<float>(), 0.0f), 1.0f);
	if (config.contains("alpha") && config["alpha"].is_number_float())
		color->a = std::min(std::max(config["alpha"].get<float>(), 0.0f), 1.0f);
}

void ColorSetting::save(json& config) {
	config.emplace(getName(), json {
		{ "red",   color->r },
		{ "green", color->g },
		{ "blue",  color->b },
		{ "alpha", color->a },
	});
}

Module::Module(std::string const& name, Category category, bool toggleable, bool need_shortcut) {
	this->name = name;
	this->category = category;
	this->toggleable = toggleable;

	shortcut = need_shortcut ? new ModuleShortcutButton(this) : nullptr;
}

Module::~Module() {
	delete shortcut;
	for (Setting* setting: settings)
		delete setting;
}

std::string const& Module::getName() {
	return name;
}

Category Module::getCategory() const {
	return category;
}

bool Module::isEnabled() const {
	return enabled;
}

bool Module::isToggleable() const {
	return toggleable;
}

ModuleShortcutButton* Module::getShortcut() {
	return shortcut;
}

std::vector<Setting*>& Module::getSettings() {
	return settings;
}

bool Module::isSettingsShowing() const {
	return settings_showing;
}

void Module::setEnabled(bool enabled) {
	this->enabled = enabled;
}

void Module::toggle(bool silence) {
	enabled = !enabled;
	if (enabled)
		onEnable();
	else
		onDisable();
	onClick();

	if (!silence)
		notification_manager.add(getName() + (enabled ? " enabled." : " disabled."));
}

void Module::toggleSettings() {
	settings_showing = !settings_showing;
}

void Module::load(json& config) { // There are so many checks because people are fucking stupid
	try {
		bool need_toggle = false;
		if (config.contains("enabled") && config["enabled"].is_boolean())
			need_toggle = enabled != config["enabled"].get<bool>();
		if (config.contains("shortcut") && config["shortcut"].is_object()) {
			json& shortcut_object = config["shortcut"];
			if (shortcut_object.contains("showing") && shortcut_object["showing"].is_boolean() && shortcut->isShowing() != shortcut_object["showing"].get<bool>())
				shortcut->toggle();
			if (shortcut_object.contains("pos") && shortcut_object["pos"].is_object()) {
				json& shortcut_pos_object = shortcut_object["pos"];
				if (shortcut_pos_object.contains("x") && shortcut_pos_object["x"].is_number_float())
					shortcut->moveX(shortcut_pos_object["x"].get<float>());
				if (shortcut_pos_object.contains("y") && shortcut_pos_object["y"].is_number_float())
					shortcut->moveY(shortcut_pos_object["y"].get<float>());
			}
		}
		for (Setting* setting: settings)
			if (config.contains(setting->getName())) {
				json& setting_config = config[setting->getName()];
				if (!setting_config.is_null())
					setting->load(setting_config);
			}
		// Toggling happens here because in "onEnable", "onDisable" or "onClick" methods can use settings values
		if (need_toggle)
			toggle(true);
	} catch (json::exception& e) {
		LOG("Failed to load config (%s): %s", name.c_str(), e.what());
	}
}

void Module::save(json& config) {
	try {
		json object {
				{ "enabled", enabled }
		};
		if (shortcut) {
			vec2_t pos = shortcut->getPos();
			object.emplace("shortcut", json {
				{ "showing", shortcut->isShowing() },
				{ "pos", {
					{ "x", pos.x },
					{ "y", pos.y },
				} }
			});
		}
		for (Setting* setting: settings)
			setting->save(object);
		config.emplace(getName(), object);
	} catch (json::exception& e) {
		LOG("Failed to save config (%s): %s", name.c_str(), e.what());
	}
}