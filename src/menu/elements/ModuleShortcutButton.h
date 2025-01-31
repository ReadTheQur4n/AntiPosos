#ifndef ANTIPOSOS_MODULESHORTCUTBUTTON_H
#define ANTIPOSOS_MODULESHORTCUTBUTTON_H

#include "FloatingButton.h"

class Module;

class ModuleShortcutButton: public FloatingButton {
private:
	Module* module;
public:
	ModuleShortcutButton(Module*);

	void draw() override;
	void onClick() override;
};

#endif //ANTIPOSOS_MODULESHORTCUTBUTTON_H
