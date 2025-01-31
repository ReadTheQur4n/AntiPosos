#ifndef ANTIPOSOS_MODULE_H
#define ANTIPOSOS_MODULE_H

#include <iostream>
#include <android/log.h>

#include "../utils/json.hpp"
#include "../memory/Game.h"
#include "../sdk/sdk.h"

using json = nlohmann::json;

class ModuleShortcutButton;

enum SettingType: uint8_t {
	BOOL = 0,
	INT,
	FLOAT,
	COLOR
};

enum Category: uint8_t {
	COMBAT = 0,
	MISC,
	MOVEMENT,
	RENDER
};

class Setting {
private:
	std::string name;
	SettingType type;
public:
	Setting(std::string const&, SettingType);

	std::string getName();
	SettingType getType();
public:
	virtual void load(json&) {};
	virtual void save(json&) {};
};

class BoolSetting: public Setting {
private:
	bool* enabled;
	std::function<void(bool)> on_toggle_callback;
public:
	BoolSetting(std::string const&, bool*, std::function<void(bool)> const& = nullptr);

	bool isEnabled();
	void setEnabled(bool);
	void toggle();
public:
	void load(json&) override;
	void save(json&) override;
};

class IntSetting: public Setting {
private:
	int* value;
	int min;
	int max;
	std::string format;
	std::function<void(int)> on_value_change_callback;
public:
	IntSetting(std::string const&, int*, int, int, std::string const& = "%i", std::function<void(int)> const& = nullptr);

	void setValue(int);

	int getValue();
	int getMin() const;
	int getMax() const;
	std::string getFormat() const;
public:
	void load(json&) override;
	void save(json&) override;
};

class FloatSetting: public Setting {
private:
	float* value;
	float min;
	float max;
	std::string format;
	std::function<void(float)> on_value_change_callback;
public:
	FloatSetting(std::string const&, float*, float, float, std::string const&, std::function<void(float)> const& = nullptr);

	void setValue(float);

	float getValue();
	float getMin() const;
	float getMax() const;
	std::string getFormat() const;
public:
	void load(json&) override;
	void save(json&) override;
};

class ColorSetting: public Setting {
private:
	vec4_t* color;
public:
	ColorSetting(std::string const&, vec4_t*);

	void setColor(vec4_t const&);

	vec4_t getColor();
public:
	void load(json&) override;
	void save(json&) override;
};

class Module {
private:
	std::string name;
	Category category;
	bool enabled = false;
	bool toggleable = false;
	ModuleShortcutButton* shortcut = nullptr;
	std::vector<Setting*> settings;
	bool settings_showing = false;
public:
	Module(std::string const&, Category, bool = true, bool = true);
	virtual ~Module();

	std::string const& getName();
	Category getCategory() const;
	bool isEnabled() const;
	bool isToggleable() const;
	ModuleShortcutButton* getShortcut();
	std::vector<Setting*>& getSettings();
	bool isSettingsShowing() const;

	template <typename T, typename ...Args> T* addSetting(Args&&... args) {
		T* setting = new T(args...);
		settings.push_back(setting);
		return setting;
	}
	void setEnabled(bool);
	void toggle(bool = false);
	void toggleSettings();
public:
	virtual void onClick() {};
	virtual void onEnable() {};
	virtual void onDisable() {};

	virtual void onDrawImGui() {};
	virtual void onTick(Level*) {};
	virtual void onSendPacket(Packet*) {};
	virtual void onReceivePacket(Packet*) {};

	virtual void load(json&);
	virtual void save(json&);
};

#endif //ANTIPOSOS_MODULE_H
