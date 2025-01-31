#ifndef ANTIPOSOS_MENU_H
#define ANTIPOSOS_MENU_H

#include "../utils/Math.h"

class AInputEvent;
class FloatingButton;
class MainButton;
class ImFont;

class Menu {
private:
	MainButton* main_button = nullptr;
	std::vector<FloatingButton*> module_shortcuts;

	bool showing = true;
	bool draw_debug_info = false;
public:
	ImFont* font32;
	ImFont* font48;
	static void init();

	bool isShowing() const;
	bool toggle();
	void handleInputEvent(AInputEvent*);
	void render();
};

extern Menu menu;

#endif
