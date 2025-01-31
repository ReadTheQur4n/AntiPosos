#ifndef ANTIPOSOS_MATH_H
#define ANTIPOSOS_MATH_H

#include <cmath>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <imgui_internal.h>
#include <string>

#define MATH_PI 3.1415926535

static constexpr float RAD_DEG = 180.0f / MATH_PI;
static constexpr float DEG_RAD = MATH_PI / 180.0f;

#define FROM_GLM4(v) vec4_t(v.x, v.y, v.z, v.w)
#define FROM_GLM3(v) vec3_t(v.x, v.y, v.z)
#define FROM_GLM2(v) vec2_t(v.x, v.y)

#define PASTE_V2(v) v.x, v.y
#define PASTE_V2_PTR(v) v->x, v->y
#define PASTE_V3(v) v.x, v.y, v.z
#define PASTE_V3_PTR(v) v->x, v->y, v->z
#define PASTE_V4(v) v.x, v.y, v.z, v.w
#define PASTE_V4_PTR(v) v->x, v->y, v->z, v->w

// If you like my code paypal me $500

struct vec2_t {
	float x, y;

	vec2_t(): x(0), y(0) {}
	vec2_t(float* arr): x(arr[0]), y(arr[1]) {}
	vec2_t(float value): x(value), y(value) {}
	vec2_t(float x, float y): x(x), y(y) {}

	float& operator[](size_t index) { return *(float*) (this + index * sizeof(float)); }
	vec2_t operator-() const { return { -x, -y }; }
	vec2_t operator+(vec2_t const& other) const { return { x + other.x, y + other.y }; }
	vec2_t operator-(vec2_t const& other) const { return { x - other.x, y - other.y }; }
	vec2_t operator*(vec2_t const& other) const { return { x * other.x, y * other.y }; }
	vec2_t operator/(vec2_t const& other) const { return { x / other.x, y / other.y }; }
	vec2_t operator+(float value) const { return { x + value, y + value }; }
	vec2_t operator-(float value) const { return { x - value, y - value }; }
	vec2_t operator*(float value) const { return { x * value, y * value }; }
	vec2_t operator/(float value) const { return { x / value, y / value }; }
	vec2_t operator++(int) { vec2_t result(*this); ++x; ++y; return result; }
	vec2_t operator--(int) { vec2_t result(*this); --x; --y; return result; }
	vec2_t& operator++() { ++x; ++y; return *this; }
	vec2_t& operator--() { --x; --y; return *this; }
	vec2_t& operator-=(vec2_t const& other) { x -= other.x; y -= other.y; return *this; }
	vec2_t& operator+=(vec2_t const& other) { x += other.x; y += other.y; return *this; }
	vec2_t& operator*=(vec2_t const& other) { x *= other.x; y *= other.y; return *this; }
	vec2_t& operator/=(vec2_t const& other) { x /= other.x; y /= other.y; return *this; }
	vec2_t& operator+=(float value) { x += value; y += value; return *this; }
	vec2_t& operator-=(float value) { x -= value; y -= value; return *this; }
	vec2_t& operator*=(float value) { x *= value; y *= value; return *this; }
	vec2_t& operator/=(float value) { x /= value; y /= value; return *this; }
	bool operator==(vec2_t const& other) const { return x == other.x && y == other.y; }
	bool operator!=(vec2_t const& other) const { return x != other.x || y != other.y; }
	bool operator==(float value) const { return x == value && y == value; }
	bool operator!=(float value) const { return x != value || y != value; }
	bool operator<(vec2_t const& other) const { return x < other.x && y < other.y; }
	bool operator>(vec2_t const& other) const { return x > other.x && y > other.y; }
	bool operator<(float value) const { return x < value && y < value; }
	bool operator>(float value) const { return x > value && y > value; }
	operator std::string() const { return to_string(); }

	vec2_t add(float value) const { return { x + value, y + value }; }
	vec2_t add(float x2, float y2) const { return { x + x2, y + y2 }; }
	vec2_t add(vec2_t const& other) const { return { x + other.x, y + other.y }; }
	vec2_t addX(float value) const { return { x + value, y }; }
	vec2_t addY(float value) const { return { x, y + value }; }

	vec2_t sub(float value) const { return { x - value, y - value }; }
	vec2_t sub(float x2, float y2) const { return { x - x2, y - y2 }; }
	vec2_t sub(vec2_t const& other) const { return { x - other.x, y - other.y }; }
	vec2_t subX(float value) const { return { x - value, y }; }
	vec2_t subY(float value) const { return { x, y - value }; }

	vec2_t mul(float value) const { return { x * value, y * value }; }
	vec2_t mul(float x2, float y2) const { return { x * x2, y * y2 }; }
	vec2_t mul(vec2_t const& other) const { return { x * other.x, y * other.y }; }
	vec2_t mulX(float value) const { return { x * value, y }; }
	vec2_t mulY(float value) const { return { x, y * value }; }

	vec2_t div(float value) const { return { x / value, y / value }; }
	vec2_t div(float x2, float y2) const { return { x / x2, y / y2 }; }
	vec2_t div(vec2_t const& other) const { return { x / other.x, y / other.y }; }
	vec2_t divX(float value) const { return { x / value, y }; }
	vec2_t divY(float value) const { return { x, y / value }; }

	float magnitude() const { return sqrtf(squaredlen()); }
	float squaredlen() const { return x * x + y * y; }
	vec2_t normalize() const { return div(magnitude()); }
	vec2_t lerp(vec2_t const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t }; };

	std::string to_string() const {
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "[%.2f, %.2f]", x, y);
		return buffer;
	}

#ifdef IMGUI_VERSION
	vec2_t(ImVec2 const& vec): x(vec.x), y(vec.y) {}

	vec2_t operator+(ImVec2 const& other) const { return { x + other.x, y + other.y }; }
	vec2_t operator-(ImVec2 const& other) const { return { x - other.x, y - other.y }; }
	vec2_t operator*(ImVec2 const& other) const { return { x * other.x, y * other.y }; }
	vec2_t operator/(ImVec2 const& other) const { return { x / other.x, y / other.y }; }

	vec2_t& operator-=(ImVec2 const& other) { x -= other.x; y -= other.y; return *this; }
	vec2_t& operator+=(ImVec2 const& other) { x += other.x; y += other.y; return *this; }
	vec2_t& operator*=(ImVec2 const& other) { x *= other.x; y *= other.y; return *this; }
	vec2_t& operator/=(ImVec2 const& other) { x /= other.x; y /= other.y; return *this; }

	bool operator==(ImVec2 const& other) const { return x == other.x && y == other.y; }
	bool operator!=(ImVec2 const& other) const { return x != other.x || y != other.y; }

	bool operator<(ImVec2 const& other) const { return x < other.x && y < other.y; }
	bool operator>(ImVec2 const& other) const { return x > other.x && y > other.y; }

	vec2_t add(ImVec2 const& other) const { return { x + other.x, y + other.y }; }
	vec2_t sub(ImVec2 const& other) const { return { x - other.x, y - other.y }; }
	vec2_t mul(ImVec2 const& other) const { return { x * other.x, y * other.y }; }
	vec2_t div(ImVec2 const& other) const { return { x / other.x, y / other.y }; }

	vec2_t lerp(ImVec2 const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t }; };

	ImVec2 to_imgui() const { return { x, y }; }
	ImVec2& as_imgui() const { return *(ImVec2*) this; }
#endif

#ifdef GLM_VERSION
	vec2_t(glm::vec2 const& vec): x(vec.x), y(vec.y) {}

	vec2_t operator+(glm::vec2 const& other) const { return { x + other.x, y + other.y }; }
	vec2_t operator-(glm::vec2 const& other) const { return { x - other.x, y - other.y }; }
	vec2_t operator*(glm::vec2 const& other) const { return { x * other.x, y * other.y }; }
	vec2_t operator/(glm::vec2 const& other) const { return { x / other.x, y / other.y }; }

	vec2_t& operator-=(glm::vec2 const& other) { x -= other.x; y -= other.y; return *this; }
	vec2_t& operator+=(glm::vec2 const& other) { x += other.x; y += other.y; return *this; }
	vec2_t& operator*=(glm::vec2 const& other) { x *= other.x; y *= other.y; return *this; }
	vec2_t& operator/=(glm::vec2 const& other) { x /= other.x; y /= other.y; return *this; }

	bool operator==(glm::vec2 const& other) const { return x == other.x && y == other.y; }
	bool operator!=(glm::vec2 const& other) const { return x != other.x || y != other.y; }

	bool operator<(glm::vec2 const& other) const { return x < other.x && y < other.y; }
	bool operator>(glm::vec2 const& other) const { return x > other.x && y > other.y; }

	vec2_t add(glm::vec2 const& other) const { return { x + other.x, y + other.y }; }
	vec2_t sub(glm::vec2 const& other) const { return { x - other.x, y - other.y }; }
	vec2_t mul(glm::vec2 const& other) const { return { x * other.x, y * other.y }; }
	vec2_t div(glm::vec2 const& other) const { return { x / other.x, y / other.y }; }

	vec2_t lerp(glm::vec2 const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t }; };

	glm::vec2 to_glm() const { return { x, y }; }
	glm::vec2& as_glm() const { return *(glm::vec2*) this; }
#endif
};

struct vec3_t {
	union {
		struct {
			float x, y, z;
		};
		struct {
			float r, g, b;
		};
		vec2_t xy;
	};

	vec3_t(): x(0), y(0), z(0) {}
	vec3_t(float* arr): x(arr[0]), y(arr[1]), z(arr[2]) {}
	vec3_t(float value): x(value), y(value), z(value) {}
	vec3_t(float x, float y, float z): x(x), y(y), z(z) {}
	vec3_t(vec2_t const& vec, float z): x(vec.x), y(vec.y), z(z) {}
	vec3_t(float x, vec2_t const& vec): x(x), y(vec.x), z(vec.y) {}

	float& operator[](size_t index) { return *(float*) (this + index * sizeof(float)); }
	vec3_t operator-() const { return { -x, -y, -z }; }
	vec3_t operator+(vec3_t const& other) const { return { x + other.x, y + other.y, z + other.z }; }
	vec3_t operator-(vec3_t const& other) const { return { x - other.x, y - other.y, z - other.z }; }
	vec3_t operator*(vec3_t const& other) const { return { x * other.x, y * other.y, z * other.z }; }
	vec3_t operator/(vec3_t const& other) const { return { x / other.x, y / other.y, z / other.z }; }
	vec3_t operator+(float value) const { return { x + value, y + value, z + value }; }
	vec3_t operator-(float value) const { return { x - value, y - value, z - value }; }
	vec3_t operator*(float value) const { return { x * value, y * value, z * value }; }
	vec3_t operator/(float value) const { return { x / value, y / value, z / value }; }
	vec3_t operator++(int) { vec3_t result(*this); ++x; ++y; ++z; return result; }
	vec3_t operator--(int) { vec3_t result(*this); --x; --y; --z; return result; }
	vec3_t& operator++() { ++x; ++y; ++z; return *this; }
	vec3_t& operator--() { --x; --y; --z; return *this; }
	vec3_t& operator+=(vec3_t const& other) { x += other.x; y += other.y; z += other.z; return *this; }
	vec3_t& operator-=(vec3_t const& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	vec3_t& operator*=(vec3_t const& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	vec3_t& operator/=(vec3_t const& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }
	vec3_t& operator+=(float value) { x += value; y += value; z += value; return *this; }
	vec3_t& operator-=(float value) { x -= value; y -= value; z -= value; return *this; }
	vec3_t& operator*=(float value) { x *= value; y *= value; z *= value; return *this; }
	vec3_t& operator/=(float value) { x /= value; y /= value; z /= value; return *this; }
	bool operator==(vec3_t const& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator!=(vec3_t const& other) const { return x != other.x || y != other.y || z != other.z; }
	bool operator==(float value) const { return x == value && y == value && z == value; }
	bool operator!=(float value) const { return x != value || y != value || z != value; }
	bool operator<(vec3_t const& other) const { return x < other.x && y < other.y && z < other.z; }
	bool operator>(vec3_t const& other) const { return x > other.x && y > other.y && z > other.z; }
	bool operator<(float value) const { return x < value && y < value && z < value; }
	bool operator>(float value) const { return x > value && y > value && z > value; }
	operator std::string() const { return to_string(); }

	vec3_t add(float value) const { return { x + value, y + value, z + value }; }
	vec3_t add(float x2, float y2, float z2) const { return { x + x2, y + y2, z + z2 }; }
	vec3_t add(vec3_t const& other) const { return { x + other.x, y + other.y, z + other.z }; }
	vec3_t addX(float value) const { return { x + value, y, z }; }
	vec3_t addY(float value) const { return { x, y + value, z }; }
	vec3_t addZ(float value) const { return { x, y, z + value }; }

	vec3_t sub(float value) const { return { x - value, y - value, z - value }; }
	vec3_t sub(float x2, float y2, float z2) const { return { x - x2, y - y2, z - z2 }; }
	vec3_t sub(vec3_t const& other) const { return { x - other.x, y - other.y, z - other.z }; }
	vec3_t subX(float value) const { return { x - value, y, z }; }
	vec3_t subY(float value) const { return { x, y - value, z }; }
	vec3_t subZ(float value) const { return { x, y, z - value }; }

	vec3_t mul(float value) const { return { x * value, y * value, z * value }; }
	vec3_t mul(float x2, float y2, float z2) const { return { x * x2, y * y2, z * z2 }; }
	vec3_t mul(vec3_t const& other) const { return { x * other.x, y * other.y, z + other.z }; }
	vec3_t mulX(float value) const { return { x * value, y, z }; }
	vec3_t mulY(float value) const { return { x, y * value, z }; }
	vec3_t mulZ(float value) const { return { x, y, z * value }; }

	vec3_t div(float value) const { return { x / value, y / value, z / value }; }
	vec3_t div(float x2, float y2, float z2) const { return { x / x2, y / y2, z / z2 }; }
	vec3_t div(vec3_t const& other) const { return { x / other.x, y / other.y, z / other.z }; }
	vec3_t divX(float value) const { return { x / value, y, z }; }
	vec3_t divY(float value) const { return { x, y / value, z }; }
	vec3_t divZ(float value) const { return { x, y, z / value }; }

	float magnitude() const { return sqrtf(squaredlen()); }
	float squaredlen() const { return x * x + y * y + z * z; }
	vec3_t normalize() const { return div(magnitude()); }
	vec3_t lerp(vec3_t const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t, z + (end.z - z ) * t }; };
	float distance(vec3_t const& other) const { return sub(other).magnitude(); }
	vec2_t angle(vec3_t const& other) const {
		vec3_t diff = other - *this;
		diff.y = diff.y / diff.magnitude();
		return { asinf(diff.y) * -RAD_DEG, (float) -atan2f(diff.x, diff.z) * RAD_DEG };
	}

	std::string to_string() const {
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "[%.2f, %.2f, %.2f]", x, y, z);
		return buffer;
	}
	int to_rgb() const {
		return (((int) (r * 255) & 0xFF) << 16) | (((int) (g * 255) & 0xFF) << 8) | ((int) (b * 255) & 0xFF);
	}

#ifdef IMGUI_VERSION
	// ImGui have no ImVec3 so there is nothing to implement
#endif

#ifdef GLM_VERSION
	vec3_t(glm::vec3 const& vec): x(vec.x), y(vec.y), z(vec.z) {}
	vec3_t(glm::vec2 const& vec, float z): x(vec.x), y(vec.y), z(z) {}
	vec3_t(float x, glm::vec2 const& vec): x(x), y(vec.x), z(vec.y) {}

	vec3_t operator+(glm::vec3 const& other) const { return { x + other.x, y + other.y, z + other.z }; }
	vec3_t operator-(glm::vec3 const& other) const { return { x - other.x, y - other.y, z - other.z }; }
	vec3_t operator*(glm::vec3 const& other) const { return { x * other.x, y * other.y, z * other.z }; }
	vec3_t operator/(glm::vec3 const& other) const { return { x / other.x, y / other.y, z / other.z }; }

	vec3_t& operator+=(glm::vec3 const& other) { x += other.x; y += other.y; z += other.z; return *this; }
	vec3_t& operator-=(glm::vec3 const& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	vec3_t& operator*=(glm::vec3 const& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	vec3_t& operator/=(glm::vec3 const& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

	bool operator==(glm::vec3 const& other) const { return x == other.x && y == other.y && z == other.z; }
	bool operator!=(glm::vec3 const& other) const { return x != other.x || y != other.y || z != other.z; }

	bool operator<(glm::vec3 const& other) const { return x < other.x && y < other.y && z < other.z; }
	bool operator>(glm::vec3 const& other) const { return x > other.x && y > other.y && z > other.z; }

	vec3_t add(glm::vec3 const& other) const { return { x + other.x, y + other.y, z + other.z }; }
	vec3_t sub(glm::vec3 const& other) const { return { x - other.x, y - other.y, z - other.z }; }
	vec3_t mul(glm::vec3 const& other) const { return { x * other.x, y * other.y, z + other.z }; }
	vec3_t div(glm::vec3 const& other) const { return { x / other.x, y / other.y, z / other.z }; }

	vec3_t lerp(glm::vec3 const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t, z + (end.z - z ) * t }; };
	float distance(glm::vec3 const& other) const { return sub(other).magnitude(); }
	vec2_t angle(glm::vec3 const& other) const {
		vec3_t diff = other - glm::vec3(x, y, z);
		diff.y = diff.y / diff.magnitude();
		return { asinf(diff.y) * -RAD_DEG, (float) -atan2f(diff.x, diff.z) * RAD_DEG };
	}

	glm::vec3 to_glm() const { return { x, y, z }; }
	glm::vec3& as_glm() const { return *(glm::vec3*) this; }
#endif
};

struct vec4_t {
	union {
		struct {
			float x, y, z, w;
		};
		struct {
			float r, g, b, a;
		};
		vec2_t xy;
		vec3_t xyz;
		vec3_t rgb;
	};

	vec4_t(): x(0), y(0), z(0), w(0) {}
	vec4_t(float* arr): x(arr[0]), y(arr[1]), z(arr[2]), w(arr[3]) {}
	vec4_t(float value): x(value), y(value), z(value), w(value) {}
	vec4_t(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
	vec4_t(vec2_t const& vec, float z, float w): x(vec.x), y(vec.y), z(z), w(w) {}
	vec4_t(float x, float y, vec2_t const& vec): x(x), y(y), z(vec.x), w(vec.y) {}
	vec4_t(vec2_t const& vec_1, vec2_t const& vec_2): x(vec_1.x), y(vec_1.y), z(vec_2.x), w(vec_2.y) {}
	vec4_t(vec3_t const& vec, float w): x(vec.x), y(vec.y), z(vec.z), w(w) {}
	vec4_t(float x, vec3_t const& vec): x(x), y(vec.x), z(vec.y), w(vec.z) {}

	float& operator[](size_t index) { return *(float*) (this + index * sizeof(float)); }
	vec4_t operator-() const { return { -x, -y, -z, -w }; }
	vec4_t operator+(vec4_t const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t operator-(vec4_t const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t operator*(vec4_t const& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
	vec4_t operator/(vec4_t const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
	vec4_t operator+(float value) const { return { x + value, y + value, z + value, w + value }; }
	vec4_t operator-(float value) const { return { x - value, y - value, z - value, w - value }; }
	vec4_t operator*(float value) const { return { x * value, y * value, z * value, w * value }; }
	vec4_t operator/(float value) const { return { x / value, y / value, z / value, w / value }; }
	vec4_t operator++(int) { vec4_t result(*this); ++x; ++y; ++z; ++w; return result; }
	vec4_t operator--(int) { vec4_t result(*this); --x; --y; --z; --w; return result; }
	vec4_t& operator++() { ++x; ++y; ++z; ++w; return *this; }
	vec4_t& operator--() { --x; --y; --z; --w; return *this; }
	vec4_t& operator+=(vec4_t const& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	vec4_t& operator-=(vec4_t const& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	vec4_t& operator*=(vec4_t const& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
	vec4_t& operator/=(vec4_t const& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }
	vec4_t& operator+=(float value) { x += value; y += value; z += value; w += value; return *this; }
	vec4_t& operator-=(float value) { x -= value; y -= value; z -= value; w -= value; return *this; }
	vec4_t& operator*=(float value) { x *= value; y *= value; z *= value; w *= value; return *this; }
	vec4_t& operator/=(float value) { x /= value; y /= value; z /= value; w /= value; return *this; }
	bool operator==(vec4_t const& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	bool operator!=(vec4_t const& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }
	bool operator==(float value) const { return x == value && y == value && z == value && w == value; }
	bool operator!=(float value) const { return x != value || y != value || z != value || w != value; }
	bool operator<(vec4_t const& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; }
	bool operator>(vec4_t const& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; }
	bool operator<(float value) const { return x < value && y < value && z < value && w < value; }
	bool operator>(float value) const { return x > value && y > value && z > value && w > value; }
	operator std::string() const { return to_string(); }

	vec4_t add(float value) const { return { x + value, y + value, z + value, w + value }; }
	vec4_t add(float x2, float y2, float z2, float w2) const { return { x + x2, y + y2, z + z2, w + w2 }; }
	vec4_t add(vec4_t const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t addX(float value) const { return { x + value, y, z, w }; }
	vec4_t addY(float value) const { return { x, y + value, z, w }; }
	vec4_t addZ(float value) const { return { x, y, z + value, w }; }
	vec4_t addW(float value) const { return { x, y, z, w + value }; }

	vec4_t sub(float value) const { return { x - value, y - value, z - value, w - value }; }
	vec4_t sub(float x2, float y2, float z2, float w2) const { return { x - x2, y - y2, z - z2, w - w2 }; }
	vec4_t sub(vec4_t const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t subX(float value) const { return { x - value, y, z, w }; }
	vec4_t subY(float value) const { return { x, y - value, z, w }; }
	vec4_t subZ(float value) const { return { x, y, z - value, w }; }
	vec4_t subW(float value) const { return { x, y, z, w - value }; }

	vec4_t mul(float value) const { return { x * value, y * value, z * value, w * value }; }
	vec4_t mul(float x2, float y2, float z2, float w2) const { return { x * x2, y * y2, z * z2, w * w2 }; }
	vec4_t mul(vec4_t const& other) const { return { x * other.x, y * other.y, z + other.z, w * other.w }; }
	vec4_t mulX(float value) const { return { x * value, y, z, w }; }
	vec4_t mulY(float value) const { return { x, y * value, z, w }; }
	vec4_t mulZ(float value) const { return { x, y, z * value, w }; }
	vec4_t mulW(float value) const { return { x, y, z, w * value }; }

	vec4_t div(float value) const { return { x / value, y / value, z / value, w / value }; }
	vec4_t div(float x2, float y2, float z2, float w2) const { return { x / x2, y / y2, z / z2, w / w2 }; }
	vec4_t div(vec4_t const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }
	vec4_t divX(float value) const { return { x / value, y, z, w }; }
	vec4_t divY(float value) const { return { x, y / value, z, w }; }
	vec4_t divZ(float value) const { return { x, y, z / value, w }; }
	vec4_t divW(float value) const { return { x, y, z, w / value }; }

	float magnitude() const { return sqrtf(squaredlen()); }
	float squaredlen() const { return x * x + y * y + z * z + w * w; }
	vec4_t normalize() const { return div(magnitude()); }
	vec4_t lerp(vec4_t const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t, z + (end.z - z ) * t, w + (end.w - w) * t }; };

	std::string to_string() const {
		char buffer[64];
		snprintf(buffer, sizeof(buffer), "[%.2f, %.2f, %.2f, %.2f]", x, y, z, w);
		return buffer;
	}
	int to_rgba() const {
		return (((int) (r * 255) & 0xFF) << 24) | (((int) (g * 255) & 0xFF) << 16) | (((int) (b * 255) & 0xFF) << 8) | ((int) (a * 255) & 0xFF);
	}
	int to_argb() const {
		return (((int) (a * 255) & 0xFF) << 24) | (((int) (r * 255) & 0xFF) << 16) | (((int) (g * 255) & 0xFF) << 8) | ((int) (b * 255) & 0xFF);
	}

#ifdef IMGUI_VERSION
	vec4_t(ImVec4 const& vec): x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	vec4_t(ImVec2 const& vec, float z, float w): x(vec.x), y(vec.y), z(z), w(w) {}
	vec4_t(float x, float y, ImVec2 const& vec): x(x), y(y), z(vec.x), w(vec.y) {}
	vec4_t(ImVec2 const& vec_1, ImVec2 const& vec_2): x(vec_1.x), y(vec_1.y), z(vec_2.x), w(vec_2.y) {}

	vec4_t operator+(ImVec4 const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t operator-(ImVec4 const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t operator*(ImVec4 const& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
	vec4_t operator/(ImVec4 const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }

	vec4_t& operator+=(ImVec4 const& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	vec4_t& operator-=(ImVec4 const& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	vec4_t& operator*=(ImVec4 const& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
	vec4_t& operator/=(ImVec4 const& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

	bool operator==(ImVec4 const& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	bool operator!=(ImVec4 const& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }

	bool operator<(ImVec4 const& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; }
	bool operator>(ImVec4 const& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; }

	vec4_t add(ImVec4 const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t sub(ImVec4 const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t mul(ImVec4 const& other) const { return { x * other.x, y * other.y, z + other.z, w * other.w }; }
	vec4_t div(ImVec4 const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }

	vec4_t lerp(ImVec4 const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t, z + (end.z - z ) * t, w + (end.w - w) * t }; };

	ImColor to_imcolor() const { return { r, g, b, a }; }
	ImVec4 to_imgui() const { return { x, y, z, w }; }
	ImVec4& as_imgui() const { return *(ImVec4*) this; }
#endif

#ifdef GLM_VERSION
	vec4_t(glm::vec4 const& vec): x(vec.x), y(vec.y), z(vec.z), w(vec.w) {}
	vec4_t(glm::vec2 const& vec, float z, float w): x(vec.x), y(vec.y), z(z), w(w) {}
	vec4_t(float x, float y, glm::vec2 const& vec): x(x), y(y), z(vec.x), w(vec.y) {}
	vec4_t(glm::vec2 const& vec_1, glm::vec2 const& vec_2): x(vec_1.x), y(vec_1.y), z(vec_2.x), w(vec_2.y) {}
	vec4_t(glm::vec3 const& vec, float w): x(vec.x), y(vec.y), z(vec.z), w(w) {}
	vec4_t(float x, glm::vec3 const& vec): x(x), y(vec.x), z(vec.y), w(vec.z) {}

	vec4_t operator+(glm::vec4 const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t operator-(glm::vec4 const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t operator*(glm::vec4 const& other) const { return { x * other.x, y * other.y, z * other.z, w * other.w }; }
	vec4_t operator/(glm::vec4 const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }

	vec4_t& operator+=(glm::vec4 const& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	vec4_t& operator-=(glm::vec4 const& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	vec4_t& operator*=(glm::vec4 const& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
	vec4_t& operator/=(glm::vec4 const& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

	bool operator==(glm::vec4 const& other) const { return x == other.x && y == other.y && z == other.z && w == other.w; }
	bool operator!=(glm::vec4 const& other) const { return x != other.x || y != other.y || z != other.z || w != other.w; }

	bool operator<(glm::vec4 const& other) const { return x < other.x && y < other.y && z < other.z && w < other.w; }
	bool operator>(glm::vec4 const& other) const { return x > other.x && y > other.y && z > other.z && w > other.w; }

	vec4_t add(glm::vec4 const& other) const { return { x + other.x, y + other.y, z + other.z, w + other.w }; }
	vec4_t sub(glm::vec4 const& other) const { return { x - other.x, y - other.y, z - other.z, w - other.w }; }
	vec4_t mul(glm::vec4 const& other) const { return { x * other.x, y * other.y, z + other.z, w * other.w }; }
	vec4_t div(glm::vec4 const& other) const { return { x / other.x, y / other.y, z / other.z, w / other.w }; }

	vec4_t lerp(glm::vec4 const& end, float t) const { return { x + (end.x - x) * t, y + (end.y - y) * t, z + (end.z - z ) * t, w + (end.w - w) * t }; };

	glm::vec4 to_glm() const { return { x, y, z, w }; }
	glm::vec4& as_glm() const { return *(glm::vec4*) this; }
#endif
};

#ifdef IMGUI_VERSION
// For vec2_t
inline ImVec2 operator+(ImVec2 const& lhs, vec2_t const& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
inline ImVec2 operator-(ImVec2 const& lhs, vec2_t const& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
inline ImVec2 operator*(ImVec2 const& lhs, vec2_t const& rhs) { return { lhs.x * rhs.x, lhs.y * rhs.y }; }
inline ImVec2 operator/(ImVec2 const& lhs, vec2_t const& rhs) { return { lhs.x / rhs.x, lhs.y / rhs.y }; }

inline ImVec2& operator-=(ImVec2& lhs, vec2_t const& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline ImVec2& operator+=(ImVec2& lhs, vec2_t const& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline ImVec2& operator*=(ImVec2& lhs, vec2_t const& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
inline ImVec2& operator/=(ImVec2& lhs, vec2_t const& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }

inline bool operator==(ImVec2 const& lhs, vec2_t const& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(ImVec2 const& lhs, vec2_t const& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }

inline bool operator<(ImVec2 const& lhs, vec2_t const& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }
inline bool operator>(ImVec2 const& lhs, vec2_t const& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y; }

// For vec4_t
inline ImVec4 operator+(ImVec4 const& lhs, vec4_t const& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w }; }
inline ImVec4 operator-(ImVec4 const& lhs, vec4_t const& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w }; }
inline ImVec4 operator*(ImVec4 const& lhs, vec4_t const& rhs) { return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w }; }
inline ImVec4 operator/(ImVec4 const& lhs, vec4_t const& rhs) { return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w }; }

inline ImVec4& operator+=(ImVec4& lhs, vec4_t const& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
inline ImVec4& operator-=(ImVec4& lhs, vec4_t const& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
inline ImVec4& operator*=(ImVec4& lhs, vec4_t const& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; lhs.w *= rhs.w; return lhs; }
inline ImVec4& operator/=(ImVec4& lhs, vec4_t const& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; lhs.w /= rhs.w; return lhs; }

inline bool operator==(ImVec4 const& lhs, vec4_t const& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline bool operator!=(ImVec4 const& lhs, vec4_t const& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline bool operator<(ImVec4 const& lhs, vec4_t const& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w; }
inline bool operator>(ImVec4 const& lhs, vec4_t const& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w; }

#endif

#ifdef GLM_VERSION
// For vec2_t
inline glm::vec2 operator+(glm::vec2 const& lhs, vec2_t const& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y }; }
inline glm::vec2 operator-(glm::vec2 const& lhs, vec2_t const& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
inline glm::vec2 operator*(glm::vec2 const& lhs, vec2_t const& rhs) { return { lhs.x * rhs.x, lhs.y * rhs.y }; }
inline glm::vec2 operator/(glm::vec2 const& lhs, vec2_t const& rhs) { return { lhs.x / rhs.x, lhs.y / rhs.y }; }

inline glm::vec2& operator-=(glm::vec2& lhs, vec2_t const& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline glm::vec2& operator+=(glm::vec2& lhs, vec2_t const& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline glm::vec2& operator*=(glm::vec2& lhs, vec2_t const& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
inline glm::vec2& operator/=(glm::vec2& lhs, vec2_t const& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }

inline bool operator==(glm::vec2 const& lhs, vec2_t const& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool operator!=(glm::vec2 const& lhs, vec2_t const& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }

inline bool operator<(glm::vec2 const& lhs, vec2_t const& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y; }
inline bool operator>(glm::vec2 const& lhs, vec2_t const& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y; }

// For vec3_t
inline glm::vec3 operator+(glm::vec3 const& lhs, vec3_t const& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z }; }
inline glm::vec3 operator-(glm::vec3 const& lhs, vec3_t const& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z }; }
inline glm::vec3 operator*(glm::vec3 const& lhs, vec3_t const& rhs) { return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z }; }
inline glm::vec3 operator/(glm::vec3 const& lhs, vec3_t const& rhs) { return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z }; }

inline glm::vec3& operator+=(glm::vec3& lhs, vec3_t const& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; return lhs; }
inline glm::vec3& operator-=(glm::vec3& lhs, vec3_t const& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; return lhs; }
inline glm::vec3& operator*=(glm::vec3& lhs, vec3_t const& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; return lhs; }
inline glm::vec3& operator/=(glm::vec3& lhs, vec3_t const& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; return lhs; }

inline bool operator==(glm::vec3 const& lhs, vec3_t const& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; }
inline bool operator!=(glm::vec3 const& lhs, vec3_t const& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z; }

inline bool operator<(glm::vec3 const& lhs, vec3_t const& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z; }
inline bool operator>(glm::vec3 const& lhs, vec3_t const& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z; }

// For vec4_t
inline glm::vec4 operator+(glm::vec4 const& lhs, vec4_t const& rhs) { return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w }; }
inline glm::vec4 operator-(glm::vec4 const& lhs, vec4_t const& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w }; }
inline glm::vec4 operator*(glm::vec4 const& lhs, vec4_t const& rhs) { return { lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w }; }
inline glm::vec4 operator/(glm::vec4 const& lhs, vec4_t const& rhs) { return { lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w }; }

inline glm::vec4& operator+=(glm::vec4& lhs, vec4_t const& rhs) { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
inline glm::vec4& operator-=(glm::vec4& lhs, vec4_t const& rhs) { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
inline glm::vec4& operator*=(glm::vec4& lhs, vec4_t const& rhs) { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; lhs.w *= rhs.w; return lhs; }
inline glm::vec4& operator/=(glm::vec4& lhs, vec4_t const& rhs) { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; lhs.w /= rhs.w; return lhs; }

inline bool operator==(glm::vec4 const& lhs, vec4_t const& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline bool operator!=(glm::vec4 const& lhs, vec4_t const& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

inline bool operator<(glm::vec4 const& lhs, vec4_t const& rhs) { return lhs.x < rhs.x && lhs.y < rhs.y && lhs.z < rhs.z && lhs.w < rhs.w; }
inline bool operator>(glm::vec4 const& lhs, vec4_t const& rhs) { return lhs.x > rhs.x && lhs.y > rhs.y && lhs.z > rhs.z && lhs.w > rhs.w; }
#endif

#endif //ANTIPOSOS_MATH_H
