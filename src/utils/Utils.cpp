#include "Utils.h"
#include "base64.h"

uintptr_t Utils::findLibrary(std::string const& library) {
	uintptr_t result = 0;
	FILE* maps = fopen("/proc/self/maps", "rt");
	char buffer[1024];

	if (maps == nullptr)
		return result;
	while (fgets(buffer, sizeof(buffer), maps))
		if (strstr(buffer, library.c_str())) {
			result = strtoull(buffer, nullptr, 16);
			break;
		}
	fclose(maps);
	return result;
}

std::string Utils::getPackageName() {
	FILE* cmdline = fopen("/proc/self/cmdline", "r");
	if (cmdline) {
		char package_name[64];
		fread(package_name, sizeof(package_name), 1, cmdline);
		fclose(cmdline);
		return package_name;
	}
	return "";
}

std::string Utils::stringFormat(std::string const& format, ...) {
	int final_n, n = ((int)format.size()) * 2;
	std::unique_ptr<char[]> formatted;
	va_list ap;
	while (true) {
		formatted.reset(new char[n]);
		strcpy(&formatted[0], format.c_str());
		va_start(ap, format);
		final_n = vsnprintf(&formatted[0], n, format.c_str(), ap);
		va_end(ap);
		if (final_n < 0 || final_n >= n)
			n += abs(final_n - n + 1);
		else
			break;
	}
	return formatted.get();
}

uint64_t Utils::getCurrentTimeMs() {
	return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

std::string Utils::b64e(std::string const& text) {
	return base64::to_base64(text);
}

std::string Utils::b64d(std::string const& text) {
	return base64::from_base64(text);
}

std::string Utils::trim(std::string const& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}