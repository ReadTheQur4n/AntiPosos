#ifndef ANTIPOSOS_APPPLATFORM_H
#define ANTIPOSOS_APPPLATFORM_H

#include <iostream>
#include <jni.h>

class AppPlatform {
public:
	uintptr_t** vtable;
public:
	jobject getMainActivity();
	void setClipboardText(std::string const&);
	std::string getClipboardText();
};

#endif //ANTIPOSOS_APPPLATFORM_H
