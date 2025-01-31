#ifndef ANTIPOSOS_UTILS_H
#define ANTIPOSOS_UTILS_H

#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>

#define LOG(...) __android_log_print(ANDROID_LOG_INFO, "AntiPosos", __VA_ARGS__)

class Utils {
public:
	static uintptr_t findLibrary(std::string const&);
	static std::string getPackageName();
	static std::string stringFormat(std::string const&, ...);
	static uint64_t getCurrentTimeMs();
	static std::string b64e(std::string const&);
	static std::string b64d(std::string const&);
	static std::string trim(std::string const&);
};

#endif //ANTIPOSOS_UTILS_H
