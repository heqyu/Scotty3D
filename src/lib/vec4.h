
#pragma once

#include <algorithm>
#include <cmath>
#include <ostream>

#include "log.h"
#include "vec3.h"

struct Vec4 {

	Vec4() {
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	explicit Vec4(float _x, float _y, float _z, float _w) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}
	explicit Vec4(float f) {
		x = y = z = w = f;
	}
	explicit Vec4(int32_t _x, int32_t _y, int32_t _z, int32_t _w) {
		x = static_cast<float>(_x);
		y = static_cast<float>(_y);
		z = static_cast<float>(_z);
		w = static_cast<float>(_w);
	}
	explicit Vec4(Vec3 xyz, float _w) {
		x = xyz.x;
		y = xyz.y;
		z = xyz.z;
		w = _w;
	}

	Vec4(const Vec4&) = default;
	Vec4& operator=(const Vec4&) = default;
	~Vec4() = default;

	float& operator[](uint32_t idx) {
		assert(idx <= 3);
		return data[idx];
	}
	float operator[](uint32_t idx) const {
		assert(idx <= 3);
		return data[idx];
	}

	Vec4 operator+=(Vec4 v) {
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}
	Vec4 operator-=(Vec4 v) {
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}
	Vec4 operator*=(Vec4 v) {
		x *= v.x;
		y *= v.y;
		z *= v.z;
		w *= v.w;
		return *this;
	}
	Vec4 operator/=(Vec4 v) {
		x /= v.x;
		y /= v.y;
		z /= v.z;
		w /= v.w;
		return *this;
	}

	Vec4 operator+=(float s) {
		x += s;
		y += s;
		z += s;
		w += s;
		return *this;
	}
	Vec4 operator-=(float s) {
		x -= s;
		y -= s;
		z -= s;
		w -= s;
		return *this;
	}
	Vec4 operator*=(float s) {
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return *this;
	}
	Vec4 operator/=(float s) {
		x /= s;
		y /= s;
		z /= s;
		w /= s;
		return *this;
	}

	Vec4 operator+(Vec4 v) const {
		return Vec4(x + v.x, y + v.y, z + v.z, w + v.w);
	}
	Vec4 operator-(Vec4 v) const {
		return Vec4(x - v.x, y - v.y, z - v.z, w - v.w);
	}
	Vec4 operator*(Vec4 v) const {
		return Vec4(x * v.x, y * v.y, z * v.z, w * v.w);
	}
	Vec4 operator/(Vec4 v) const {
		return Vec4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	Vec4 operator+(float s) const {
		return Vec4(x + s, y + s, z + s, w + s);
	}
	Vec4 operator-(float s) const {
		return Vec4(x - s, y - s, z - s, w - s);
	}
	Vec4 operator*(float s) const {
		return Vec4(x * s, y * s, z * s, w * s);
	}
	Vec4 operator/(float s) const {
		return Vec4(x / s, y / s, z / s, w / s);
	}

	bool operator==(Vec4 v) const {
		return x == v.x && y == v.y && z == v.z && w == v.w;
	}
	bool operator!=(Vec4 v) const {
		return x != v.x || y != v.y || z != v.z || w != v.w;
	}

	/// Absolute value
	Vec4 abs() const {
		return Vec4(std::abs(x), std::abs(y), std::abs(z), std::abs(w));
	}
	/// Negation
	Vec4 operator-() const {
		return Vec4(-x, -y, -z, -w);
	}
	/// Are all members real numbers?
	bool valid() const {
		return std::isfinite(x) && std::isfinite(y) && std::isfinite(z) && std::isfinite(w);
	}

	/// Modify vec to have unit length
	Vec4 normalize() {
		float n = norm();
		x /= n;
		y /= n;
		z /= n;
		w /= n;
		return *this;
	}
	/// Return unit length vec in the same direction
	Vec4 unit() const {
		float n = norm();
		return Vec4(x / n, y / n, z / n, w / n);
	}

	float norm_squared() const {
		return x * x + y * y + z * z + w * w;
	}
	float norm() const {
		return std::sqrt(norm_squared());
	}

	/// Returns first three components
	Vec3 xyz() const {
		return Vec3(x, y, z);
	}
	/// Returns first two components
	Vec2 xy() const {
		return Vec2(x, y);
	}

	/// Performs perspective division (xyz/w)
	Vec3 project() const {
		return Vec3(x / w, y / w, z / w);
	}

	bool approx_equal(const Vec3& o) const {
		return eps::approx_equal<float,3>(data, o.data);
	}

	union {
		struct {
			float x;
			float y;
			float z;
			float w;
		};
		float data[4] = {};
	};
};

inline Vec4 operator+(float s, Vec4 v) {
	return Vec4(v.x + s, v.y + s, v.z + s, v.w + s);
}
inline Vec4 operator-(float s, Vec4 v) {
	return Vec4(v.x - s, v.y - s, v.z - s, v.w - s);
}
inline Vec4 operator*(float s, Vec4 v) {
	return Vec4(v.x * s, v.y * s, v.z * s, v.w * s);
}
inline Vec4 operator/(float s, Vec4 v) {
	return Vec4(s / v.x, s / v.y, s / v.z, s / v.w);
}

/// Take minimum of each component
inline Vec4 hmin(Vec4 l, Vec4 r) {
	return Vec4(std::min(l.x, r.x), std::min(l.y, r.y), std::min(l.z, r.z), std::min(l.w, r.w));
}
/// Take maximum of each component
inline Vec4 hmax(Vec4 l, Vec4 r) {
	return Vec4(std::max(l.x, r.x), std::max(l.y, r.y), std::max(l.z, r.z), std::max(l.w, r.w));
}

/// 4D dot product
inline float dot(Vec4 l, Vec4 r) {
	return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
}

inline std::string to_string(Vec4 const &v) {
	return "(" + std::to_string(v.x) + ", " + std::to_string(v.y) + ", " + std::to_string(v.z) + ", " + std::to_string(v.w) + ")";
}

inline std::ostream& operator<<(std::ostream& out, Vec4 v) {
	out << "{" << v.x << "," << v.y << "," << v.z << "," << v.w << "}";
	return out;
}
