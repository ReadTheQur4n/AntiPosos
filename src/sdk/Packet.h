#ifndef ANTIPOSOS_PACKET_H
#define ANTIPOSOS_PACKET_H

#include <string>

#include "../utils/Math.h"
#include "Block.h"

class Actor;

enum PacketId: int {
	LOGIN_PACKET = 1,
	PLAY_STATUS_PACKET = 2,
	SERVER_TO_CLIENT_HANDSHAKE_PACKET = 3,
	CLIENT_TO_SERVER_HANDSHAKE_PACKET = 4,
	DISCONNECT_PACKET = 5,
	RESOURCE_PACKS_INFO_PACKET = 6,
	RESOURCE_PACK_STACK_PACKET = 7,
	RESOURCE_PACK_CLIENT_RESPONSE_PACKET = 8,
	TEXT_PACKET = 9,
	SET_TIME_PACKET = 10,
	START_GAME_PACKET = 11,
	ADD_PLAYER_PACKET = 12,
	ADD_ACTOR_PACKET = 13,
	REMOVE_ACTOR_PACKET = 14,
	ADD_ITEM_ACTOR_PACKET = 15,
	SERVER_PLAYER_POST_MOVE_POSITION_PACKET = 16,
	TAKE_ITEM_ACTOR_PACKET = 17,
	MOVE_ACTOR_ABSOLUTE_PACKET = 18,
	MOVE_PLAYER_PACKET = 19,
	PASSENGER_JUMP_PACKET = 20,
	UPDATE_BLOCK_PACKET = 21,
	ADD_PAINTING_PACKET = 22,
	LEVEL_SOUND_EVENT_PACKET_V1 = 24,
	LEVEL_EVENT_PACKET = 25,
	BLOCK_EVENT_PACKET = 26,
	ACTOR_EVENT_PACKET = 27,
	MOB_EFFECT_PACKET = 28,
	UPDATE_ATTRIBUTES_PACKET = 29,
	INVENTORY_TRANSACTION_PACKET = 30,
	MOB_EQUIPMENT_PACKET = 31,
	MOB_ARMOR_EQUIPMENT_PACKET = 32,
	INTERACT_PACKET = 33,
	BLOCK_PICK_REQUEST_PACKET = 34,
	ACTOR_PICK_REQUEST_PACKET = 35,
	PLAYER_ACTION_PACKET = 36,
	HURT_ARMOR_PACKET = 38,
	SET_ACTOR_DATA_PACKET = 39,
	SET_ACTOR_MOTION_PACKET = 40,
	SET_ACTOR_LINK_PACKET = 41,
	SET_HEALTH_PACKET = 42,
	SET_SPAWN_POSITION_PACKET = 43,
	ANIMATE_PACKET = 44,
	RESPAWN_PACKET = 45,
	CONTAINER_OPEN_PACKET = 46,
	CONTAINER_CLOSE_PACKET = 47,
	PLAYER_HOTBAR_PACKET = 48,
	INVENTORY_CONTENT_PACKET = 49,
	INVENTORY_SLOT_PACKET = 50,
	CONTAINER_SET_DATA_PACKET = 51,
	CRAFTING_DATA_PACKET = 52,
	GUI_DATA_PICK_ITEM_PACKET = 54,
	BLOCK_ACTOR_DATA_PACKET = 56,
	PLAYER_INPUT_PACKET = 57,
	LEVEL_CHUNK_PACKET = 58,
	SET_COMMANDS_ENABLED_PACKET = 59,
	SET_DIFFICULTY_PACKET = 60,
	CHANGE_DIMENSION_PACKET = 61,
	SET_PLAYER_GAME_TYPE_PACKET = 62,
	PLAYER_LIST_PACKET = 63,
	SIMPLE_EVENT_PACKET = 64,
	LEGACY_TELEMETRY_EVENT_PACKET = 65,
	SPAWN_EXPERIENCE_ORB_PACKET = 66,
	CLIENTBOUND_MAP_ITEM_DATA_PACKET = 67,
	MAP_INFO_REQUEST_PACKET = 68,
	REQUEST_CHUNK_RADIUS_PACKET = 69,
	CHUNK_RADIUS_UPDATED_PACKET = 70,
	GAME_RULES_CHANGED_PACKET = 72,
	CAMERA_PACKET = 73,
	BOSS_EVENT_PACKET = 74,
	SHOW_CREDITS_PACKET = 75,
	AVAILABLE_COMMANDS_PACKET = 76,
	COMMAND_REQUEST_PACKET = 77,
	COMMAND_BLOCK_UPDATE_PACKET = 78,
	COMMAND_OUTPUT_PACKET = 79,
	UPDATE_TRADE_PACKET = 80,
	UPDATE_EQUIP_PACKET = 81,
	RESOURCE_PACK_DATA_INFO_PACKET = 82,
	RESOURCE_PACK_CHUNK_DATA_PACKET = 83,
	RESOURCE_PACK_CHUNK_REQUEST_PACKET = 84,
	TRANSFER_PACKET = 85,
	PLAY_SOUND_PACKET = 86,
	STOP_SOUND_PACKET = 87,
	SET_TITLE_PACKET = 88,
	ADD_BEHAVIOR_TREE_PACKET = 89,
	STRUCTURE_BLOCK_UPDATE_PACKET = 90,
	SHOW_STORE_OFFER_PACKET = 91,
	PURCHASE_RECEIPT_PACKET = 92,
	PLAYER_SKIN_PACKET = 93,
	SUB_CLIENT_LOGIN_PACKET = 94,
	AUTOMATION_CLIENT_CONNECT_PACKET = 95,
	SET_LAST_HURT_BY_PACKET = 96,
	BOOK_EDIT_PACKET = 97,
	NPC_REQUEST_PACKET = 98,
	PHOTO_TRANSFER_PACKET = 99,
	MODAL_FORM_REQUEST_PACKET = 100,
	MODAL_FORM_RESPONSE_PACKET = 101,
	SERVER_SETTINGS_REQUEST_PACKET = 102,
	SERVER_SETTINGS_RESPONSE_PACKET = 103,
	SHOW_PROFILE_PACKET = 104,
	SET_DEFAULT_GAME_TYPE_PACKET = 105,
	REMOVE_OBJECTIVE_PACKET = 106,
	SET_DISPLAY_OBJECTIVE_PACKET = 107,
	SET_SCORE_PACKET = 108,
	LAB_TABLE_PACKET = 109,
	UPDATE_BLOCK_SYNCED_PACKET = 110,
	MOVE_ACTOR_DELTA_PACKET = 111,
	SET_SCOREBOARD_IDENTITY_PACKET = 112,
	SET_LOCAL_PLAYER_AS_INITIALIZED_PACKET = 113,
	UPDATE_SOFT_ENUM_PACKET = 114,
	NETWORK_STACK_LATENCY_PACKET = 115,
	SPAWN_PARTICLE_EFFECT_PACKET = 118,
	AVAILABLE_ACTOR_IDENTIFIERS_PACKET = 119,
	LEVEL_SOUND_EVENT_PACKET_V2 = 120,
	NETWORK_CHUNK_PUBLISHER_UPDATE_PACKET = 121,
	BIOME_DEFINITION_LIST_PACKET = 122,
	LEVEL_SOUND_EVENT_PACKET = 123,
	LEVEL_EVENT_GENERIC_PACKET = 124,
	LECTERN_UPDATE_PACKET = 125,
	CLIENT_CACHE_STATUS_PACKET = 129,
	ON_SCREEN_TEXTURE_ANIMATION_PACKET = 130,
	MAP_CREATE_LOCKED_COPY_PACKET = 131,
	STRUCTURE_TEMPLATE_DATA_REQUEST_PACKET = 132,
	STRUCTURE_TEMPLATE_DATA_RESPONSE_PACKET = 133,
	CLIENT_CACHE_BLOB_STATUS_PACKET = 135,
	CLIENT_CACHE_MISS_RESPONSE_PACKET = 136,
	EDUCATION_SETTINGS_PACKET = 137,
	EMOTE_PACKET = 138,
	MULTIPLAYER_SETTINGS_PACKET = 139,
	SETTINGS_COMMAND_PACKET = 140,
	ANVIL_DAMAGE_PACKET = 141,
	COMPLETED_USING_ITEM_PACKET = 142,
	NETWORK_SETTINGS_PACKET = 143,
	PLAYER_AUTH_INPUT_PACKET = 144,
	CREATIVE_CONTENT_PACKET = 145,
	PLAYER_ENCHANT_OPTIONS_PACKET = 146,
	ITEM_STACK_REQUEST_PACKET = 147,
	ITEM_STACK_RESPONSE_PACKET = 148,
	PLAYER_ARMOR_DAMAGE_PACKET = 149,
	CODE_BUILDER_PACKET = 150,
	UPDATE_PLAYER_GAME_TYPE_PACKET = 151,
	EMOTE_LIST_PACKET = 152,
	POSITION_TRACKING_DB_SERVER_BROADCAST_PACKET = 153,
	POSITION_TRACKING_DB_CLIENT_REQUEST_PACKET = 154,
	DEBUG_INFO_PACKET = 155,
	PACKET_VIOLATION_WARNING_PACKET = 156,
	MOTION_PREDICTION_HINTS_PACKET = 157,
	ANIMATE_ENTITY_PACKET = 158,
	CAMERA_SHAKE_PACKET = 159,
	PLAYER_FOG_PACKET = 160,
	CORRECT_PLAYER_MOVE_PREDICTION_PACKET = 161,
	ITEM_COMPONENT_PACKET = 162,
	CLIENTBOUND_DEBUG_RENDERER_PACKET = 164,
	SYNC_ACTOR_PROPERTY_PACKET = 165,
	ADD_VOLUME_ENTITY_PACKET = 166,
	REMOVE_VOLUME_ENTITY_PACKET = 167,
	SIMULATION_TYPE_PACKET = 168,
	NPC_DIALOGUE_PACKET = 169,
	EDU_URI_RESOURCE_PACKET = 170,
	CREATE_PHOTO_PACKET = 171,
	UPDATE_SUB_CHUNK_BLOCKS_PACKET = 172,
	SUB_CHUNK_PACKET = 174,
	SUB_CHUNK_REQUEST_PACKET = 175,
	PLAYER_START_ITEM_COOLDOWN_PACKET = 176,
	SCRIPT_MESSAGE_PACKET = 177,
	CODE_BUILDER_SOURCE_PACKET = 178,
	TICKING_AREAS_LOAD_STATUS_PACKET = 179,
	DIMENSION_DATA_PACKET = 180,
	AGENT_ACTION_EVENT_PACKET = 181,
	CHANGE_MOB_PROPERTY_PACKET = 182,
	LESSON_PROGRESS_PACKET = 183,
	REQUEST_ABILITY_PACKET = 184,
	REQUEST_PERMISSIONS_PACKET = 185,
	TOAST_REQUEST_PACKET = 186,
	UPDATE_ABILITIES_PACKET = 187,
	UPDATE_ADVENTURE_SETTINGS_PACKET = 188,
	DEATH_INFO_PACKET = 189,
	EDITOR_NETWORK_PACKET = 190,
	FEATURE_REGISTRY_PACKET = 191,
	SERVER_STATS_PACKET = 192,
	REQUEST_NETWORK_SETTINGS_PACKET = 193,
	GAME_TEST_REQUEST_PACKET = 194,
	GAME_TEST_RESULTS_PACKET = 195,
	UPDATE_CLIENT_INPUT_LOCKS_PACKET = 196,
	CAMERA_PRESETS_PACKET = 198,
	UNLOCKED_RECIPES_PACKET = 199,
	CAMERA_INSTRUCTION_PACKET = 300,
	COMPRESSED_BIOME_DEFINITION_LIST_PACKET = 301,
	TRIM_DATA_PACKET = 302,
	OPEN_SIGN_PACKET = 303,
	AGENT_ANIMATION_PACKET = 304,
	REFRESH_ENTITLEMENTS_PACKET = 305,
	PLAYER_TOGGLE_CRAFTER_SLOT_REQUEST_PACKET = 306,
	SET_PLAYER_INVENTORY_OPTIONS_PACKET = 307,
	SET_HUD_PACKET = 308,
	AWARD_ACHIEVEMENT_PACKET = 309,
	CLIENTBOUND_CLOSE_FORM_PACKET = 310,
	SERVERBOUND_LOADING_SCREEN_PACKET = 312,
	JIGSAW_STRUCTURE_DATA_PACKET = 313,
	CURRENT_STRUCTURE_FEATURE_PACKET = 314,
	SERVERBOUND_DIAGNOSTICS_PACKET = 315,
	CAMERA_AIM_ASSIST_PACKET = 316,
	CONTAINER_REGISTRY_CLEANUP_PACKET = 317,
	MOVEMENT_EFFECT_PACKET = 318,
	SET_MOVEMENT_AUTHORITY_PACKET = 319,
	END // Not the packet id
};

class Packet;
class LoopbackPacketSender {
public:
	uintptr_t** vtable;
public:
	void send(Packet*);
};

class Packet {
public:
	uintptr_t** vtable;
	int priority;
	uint8_t sub_client_id;
	int reliability;
	bool handled;
	std::chrono::steady_clock::time_point receive_time_point;
	uintptr_t handler;
	int compressible;
public:
	PacketId getId();
	std::string getName();

	static std::shared_ptr<Packet> create(PacketId);
};

class TextPacket: public Packet {
public:
	enum Type: uint8_t {
		RAW = 0,
		CHAT = 1,
		TRANSLATION = 2,
		POPUP = 3,
		JUKEBOX_POPUP = 4,
		TIP = 5,
		SYSTEM = 6,
		WHISPER = 7,
		ANNOUNCEMENT = 8,
		JSON_WHISPER = 9,
		JSON = 10,
		JSON_ANNOUNCEMENT = 11
	};
public:
	Type type;
	bool need_translate;
	std::string source; // not empty if type equals Type::CHAT or Type::WHISPER or Type::ANNOUNCEMENT
	std::string message;
	std::vector<std::string> params;
	std::string xuid;
	std::string platform_id;
	std::string filtered_message;
};

class MovePlayerPacket: public Packet {
public:
	enum Mode: uint8_t {
		NORMAL = 0,
		RESET = 1,
		TELEPORT = 2,
		PITCH = 3 // OnlyHeadRot?
	};
public:
	 uint64_t actor_runtime_id;
	 vec3_t pos;
	 vec2_t rot;
	 float body_yaw;
	 Mode mode; // Determines how the client will behave when receiving this, see the enum for details. When sent to the server this is always 'Normal' except when in a vehicle then it's 'OnlyHeadRot'.
	 bool on_ground;
	 uint64_t riding_actor_runtime_id;
	 int teleportation_cause; // Always zero if server bound.
	 int source_actor_type; // Always zero if server bound.
};

class LevelSoundEventPacket: public Packet {
public:
	int event;
	vec3_t pos;
	int data;
	std::string actor_id; // idk what is that
	bool baby_mob;
	bool global;
};

class InteractPacket: public Packet {
public:
	enum Action: uint8_t {
		LEAVE_VEHICLE = 3,
		MOUSEOVER = 4,
		OPEN_NPC = 5,
		OPEN_INVENTORY = 6
	};
public:
	Action action;
	uint64_t target_runtime_id;
	vec3_t some_shit; // not empty if action equals LEAVE_VEHICLE or MOUSEOVER
};

class BlockPickRequestPacket: public Packet {
public:
	BlockPos pos;
	bool add_user_data;
	uint8_t max_slots;
};

class SetActorMotionPacket: public Packet {
public:
	uint64_t actor_runtime_id;
	vec3_t motion;
};

class AnimatePacket: public Packet {
public:
	enum Action: uint8_t {
		SWING_ARM = 1,
		STOP_SLEEP = 3,
		CRITICAL_HIT = 4,
		MAGICAL_CRITICAL_HIT = 5,
		ROW_RIGHT = 128,
		ROW_LEFT = 129
	};
public:
	uint64_t actor_runtime_id;
	Action action;
	float some_shit; // not empty if action & 0x80 != 0 (maybe it is a boat rowing time, i don't know)
};

class PlayerInputPacket: public Packet {
public:
	vec2_t motion;
	bool jumping;
	bool sneaking;
};

class EmotePacket: public Packet {
public:
	uint64_t actor_runtime_id;
	std::string emote_id;
	int emote_length_ticks;
	std::string xuid;
	std::string platform_id;
	uint8_t flags;
};

class PlayerAuthInputPacket: public Packet {
public:
	// Copy-pasted from PocketMine
	enum InputData: int {
		// Pressing the "fly up" key when using touch.
		ASCEND = 0,
		// Pressing the "fly down" key when using touch.
		DESCEND = 1,
		// Pressing (and optionally holding) the jump key (while not flying).
		NORTH_JUMP = 2,
		// Pressing (and optionally holding) the jump key (including while flying).
		JUMP_DOWN = 3,
		// Pressing (and optionally holding) the sprint key (typically the CTRL key). Does not include double-pressing the forward key.
		SPRINT_DOWN = 4,
		// Pressing (and optionally holding) the fly button ONCE when in flight mode when using touch. This has no obvious use.
		CHANGE_HEIGHT = 5,
		// Pressing (and optionally holding) the jump key (including while flying), and also auto-jumping.
		JUMPING = 6,
		// Auto-swimming upwards while pressing forwards with auto-jump enabled.
		AUTO_JUMPING_IN_WATER = 7,
		// Sneaking, and pressing the "fly down" key or "sneak" key (including while flying).
		SNEAKING = 8,
		// Pressing (and optionally holding) the sneak key (including while flying). This includes when the sneak button is toggled ON with touch controls.
		SNEAK_DOWN = 9,
		// Pressing the forward key (typically W on keyboard).
		UP = 10,
		// Pressing the backward key (typically S on keyboard).
		DOWN = 11,
		// Pressing the left key (typically A on keyboard).
		LEFT = 12,
		// Pressing the right key (typically D on keyboard).
		RIGHT = 13,
		// Pressing the ↖ key on touch.
		UP_LEFT = 14,
		// Pressing the ↗ key on touch.
		UP_RIGHT = 15,
		// Client wants to go upwards. Sent when Ascend or Jump is pressed, irrespective of whether flight is enabled.
		WANT_UP = 16,
		// Client wants to go downwards. Sent when Descend or Sneak is pressed, irrespective of whether flight is enabled.
		WANT_DOWN = 17,
		// Same as "want up" but slow. Only usable with controllers at the time of writing. Triggered by pressing the right joystick by default.
		WANT_DOWN_SLOW = 18,
		// Same as "want down" but slow. Only usable with controllers at the time of writing. Not bound to any control by default.
		WANT_UP_SLOW = 19,
		// Unclear usage, during testing it was only seen in conjunction with SPRINT_DOWN. NOT sent while actually sprinting.
		SPRINTING = 20,
		// Ascending scaffolding. Note that this is NOT sent when climbing ladders.
		ASCEND_BLOCK = 21,
		// Descending scaffolding.
		DESCEND_BLOCK = 22,
		// Toggling the sneak button on touch when the button enters the "enabled" state.
		SNEAK_TOGGLE_DOWN = 23,
		// Unclear use. Sent continually on touch controls, irrespective of whether the player is actually sneaking or not.
		PERSIST_SNEAK = 24,
		START_SPRINTING = 25,
		STOP_SPRINTING = 26,
		START_SNEAKING = 27,
		STOP_SNEAKING = 28,
		START_SWIMMING = 29,
		STOP_SWIMMING = 30,
		// Initiating a new jump. Sent every time the client leaves the ground due to jumping, including auto jumps.
		START_JUMPING = 31,
		START_GLIDING = 32,
		STOP_GLIDING = 33,
		PERFORM_ITEM_INTERACTION = 34,
		PERFORM_BLOCK_ACTIONS = 35,
		PERFORM_ITEM_STACK_REQUEST = 36,
		HANDLED_TELEPORT = 37,
		EMOTING = 38,
		// Left-clicking the air. In vanilla, this generates an ATTACK_NO_DAMAGE sound and does nothing else.
		MISSED_SWING = 39,
		START_CRAWLING = 40,
		STOP_CRAWLING = 41,
		START_FLYING = 42,
		STOP_FLYING = 43,
		ACK_ACTOR_DATA = 44,
		IN_CLIENT_PREDICTED_VEHICLE = 45,
		PADDLING_LEFT = 46,
		PADDLING_RIGHT = 47,
		BLOCK_BREAKING_DELAY_ENABLED = 48,
		HORIZONTAL_COLLISION = 49,
		VERTICAL_COLLISION = 50,
		DOWN_LEFT = 51,
		DOWN_RIGHT = 52,
		START_USING_ITEM = 53,
		IS_CAMERA_RELATIVE_MOVEMENT_ENABLED = 54,
		IS_ROT_CONTROLLED_BY_MOVE_DIRECTION = 55,
		START_SPIN_ATTACK = 56,
		STOP_SPIN_ATTACK = 57,
	};
public:
	char filler[160];
};

#endif //ANTIPOSOS_PACKET_H
