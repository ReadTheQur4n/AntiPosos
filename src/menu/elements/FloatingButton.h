#ifndef ANTIPOSOS_FLOATINGBUTTON_H
#define ANTIPOSOS_FLOATINGBUTTON_H

#include <imgui.h>
#include <string>
#include "../../utils/Math.h"
#include <android/input.h>

// A zone where is it forbidden to move the button
#define SAFE_ZONE 10.0f

class FloatingButton {
protected:
	bool showing = false;
	vec2_t pos = 0.0f;
	vec2_t size = 100.0f;
public:
	struct {
		bool clicked = false;
		bool moving = false;
		int pointer_index = -1;
		vec2_t moving_delta = 0.0f;
		vec2_t start_pos = 0.0f;
		//vec2_t size_delta = 0.0f; //para el efecto cuando se mueve en relacion con el lugar donde se presiona el boton, no usado
	} drag;
public:
	FloatingButton(vec2_t const&, vec2_t const&);

	bool isShowing() const;
	vec2_t getPos() const;
	vec2_t getSize() const;
	bool isIntersects(vec2_t const&) const;

	void toggle();
	void move(vec2_t const&);
	void moveX(float);
	void moveY(float);
	bool handleInputEvent(AInputEvent*);
public:
	virtual void draw() = 0;
	virtual void onClick() = 0;
};

#endif
