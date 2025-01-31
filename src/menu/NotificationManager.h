#ifndef ANTIPOSOS_NOTIFICATIONMANAGER_H
#define ANTIPOSOS_NOTIFICATIONMANAGER_H

#include <deque>
#include <string>
#include "../utils/Math.h"

struct Notification {
	enum State: uint8_t {
		NONE = 0,
		IN = 1,
		STAY = 2,
		OUT = 3
	};
	uint64_t start_time = 0;
	uint64_t end_time = 0;
	uint64_t duration = 500;
	State state = State::IN;
	std::string text;
	vec2_t offset = 0.0f; // from 0 to 1 vector
	Notification(std::string const&, uint64_t, uint64_t = 500);

	bool fade(uint64_t current_time);
	State getNextState() const;
};

class NotificationManager {
private:
	std::deque<Notification> queue;
public:
	void add(std::string const& text);
	void render();
	//void update(); implemented in render()
};

extern NotificationManager notification_manager;

#endif //ANTIPOSOS_NOTIFICATIONMANAGER_H
