#include "NotificationManager.h"
#include "../utils/Utils.h"
#include <imgui.h>
#include "../memory/Game.h"
#include "Menu.h"
#include <GLES3/gl32.h>

NotificationManager notification_manager;

Notification::Notification(std::string const& text, uint64_t start_time, uint64_t duration) {
	this->text = text;
	this->start_time = start_time;
	this->duration = duration;
	end_time = start_time + duration;
}

Notification::State Notification::getNextState() const {
	switch (state) {
		case State::NONE:
		case State::OUT: return State::NONE; break; // breaks not necessary
		case State::STAY: return State::OUT; break;
		case State::IN: return State::STAY; break;
		default: return State::NONE; break;
	}
}

bool Notification::fade(uint64_t ms) {
	if (ms < end_time) {
		float a =  fminf(fmaxf((float) (ms - start_time) / (float) duration, 0.0f), 1.0f);
		if (state == State::OUT)
			offset = offset.lerp(0.0f, a);
		else if (state == State::IN)
			offset = offset.lerp(1.0f, a);
	} else {
		state = getNextState();
		start_time = ms;
		end_time = ms + duration;
	}
	return state != State::NONE; // tells that it is showing
}

void NotificationManager::add(std::string const& text) {
	queue.emplace_back(text, Utils::getCurrentTimeMs());
}

void NotificationManager::render() {
	auto ms = Utils::getCurrentTimeMs();
	while (!queue.empty()) { // clean up
		auto& next = queue.front();
		if (!next.fade(ms)) {
			queue.pop_front();
			continue;
		}
		break;
	}
	vec2_t topmost = game.screen_size.subY(150.0f);
	auto draw_list = ImGui::GetBackgroundDrawList();
	static vec2_t spacing { 150.0f, 60.0f };
	ImGui::PushFont(menu.font48);
	for (auto& i: queue) {
		i.fade(ms); // double fade LOL
		const char* text = i.text.c_str();
		ImVec2 text_size = ImGui::CalcTextSize(text);
		vec2_t size = spacing + text_size;
		draw_list->AddRectFilled(topmost.subX(size.x * i.offset.x).as_imgui(), topmost.addY(size.y).as_imgui(), IM_COL32(0, 0, 0, 150), 10.0f, ImDrawFlags_RoundCornersLeft);
		draw_list->AddText((topmost.subX(size.x * i.offset.x) + (size - text_size) / 2).as_imgui(), IM_COL32(255, 255, 255, 255), text, nullptr);
		topmost.y -= (size.y + 10) * i.offset.y;
	}
	ImGui::PopFont();
}