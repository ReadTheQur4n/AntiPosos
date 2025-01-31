#ifndef ANTIPOSOS_MAINBUTTON_H
#define ANTIPOSOS_MAINBUTTON_H

#include "elements/FloatingButton.h"

class MainButton: public FloatingButton {
public:
	MainButton();

	void draw() override;
	void onClick() override;
};

#endif
