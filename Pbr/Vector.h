#pragma once
#include "MathDef.h"
#include <assert.h>
#include <iostream>

template<typename T>
class Vector3
{
public:
	Vector3() : x(0), y(0), z(0) {}
	Vector3(T x, T y, T z) : x(x), y(y), z(z) { assert(!HasNaNs()); }
	Vector3(T scaler) :x(scaler), y(scaler), z(scaler) { assert(!HasNaNs()); }
	Vector3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z) { assert(!v.HasNaNs()); }
public:
	bool HasNaNs() const{return std::isnan(x) || std::isnan(y) || std::isnan(z);}
public:
	T operator[](int index) const{
		assert(index >= 0 && index < 3);
		if (index == 0)return x;
		if (index == 1)return y;
		return z;
	}
	T& operator[](int index)
	{
		assert(index >= 0 && index < 3);
		if (index == 0)return x;
		if (index == 1)return y;
		return z;
	}
	Vector3& operator+=(const Vector3<T>& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	}
	Vector3  operator+(const Vector3<T>& v) const
	{
		return Vector3<T>(x + v.x, y + v.y, z + v.z);
	}
	Vector3& operator-=(const Vector3<T>& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	}
	Vector3  operator-(const Vector3<T>& v) const
	{
		return Vector3<T>(x - v.x, y - v.y, z - v.z);
	}
	Vector3& operator*=(const Vector3<T>& v)
	{
		x *= v.x; y *= v.y; z *= v.z;
		return *this;
	}
	Vector3  operator*(const Vector3<T>& v) const
	{
		return Vector3<T>(x * v.x, y * v.y, z * v.z);
	}
	Vector3& operator/=(const Vector3<T>& v)
	{
		x /= v.x; y /= v.y; z /= v.z;
		return *this;
	}
	Vector3  operator/(const Vector3<T>& v) const
	{
		return Vector3<T>(x / v.x, y / v.y, z / v.z);
	}

	Vector3& operator/=(T scaler)
	{
		assert(scaler != 0);
		T inv_scaler = (T)1 / scaler;
		x *= inv_scaler;
		y *= inv_scaler;
		z *= inv_scaler;
		return *this;
	}

	Vector3 operator/(T scaler)const
	{
		assert(scaler != 0);
		T inv_scaler = (T)1 / scaler;
		return Vector3<T>(x * inv_scaler, y * inv_scaler, z * inv_scaler);
	}

	Vector3 operator-()const{return Vector3<T>(-x, -y, -z);}
public:
	inline T LengthSquared()const {
		return x * x + y * y + z * z;
	}
	inline T Length()const
	{
		return std::sqrt(LengthSquared());
	}
	void Normalize() {
		(*this) /= Length();
	}
public:
	friend inline Vector3<T> operator+(T s, const Vector3<T> v)
	{
		return v + s;
	}
	friend inline Vector3<T> operator-(T s, const Vector3<T> v)
	{
		return Vector3<T>(s - v.x, s - v.y, s - v.z);
	}
	friend inline Vector3<T> operator*(T s, const Vector3<T> v)
	{
		return v * s;
	}
	friend inline Vector3<T> operator/(T s, const Vector3<T> v)
	{
		return Vector3<T>(s / v.x, s / v.y, s / v.z);
	}
	friend inline std::ostream& operator<<(std::ostream& os, const Vector3<T>& v) {
		os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
		return os;
	}
	friend inline Vector3<T> abs(const Vector3<T>& v){
		return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
	}
	friend inline Vector3<T> floor(const Vector3<T>& v1) {
		return Vector3<T>(std::floor(v1.x), std::floor(v1.y), std::floor(v1.z));
	}
	friend inline Vector3<T> ceil(const Vector3<T>& v1) {
		return Vector3<T>(std::ceil(v1.x), std::ceil(v1.y), std::ceil(v1.z));
	}
	friend inline T dot(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
	}
	friend inline Vector3<T> cross(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(lhs.y * rhs.z - lhs.z * rhs.y, lhs.z * rhs.x - lhs.x * rhs.z, lhs.x * rhs.y - lhs.y * rhs.x);
	}
	friend inline Vector3<T> normalize(const Vector3<T>& v) {
		return v / v.Length();
	}
	friend inline T MinComponent(const Vector3<T>& v) {
		return std::fmin(v.x, std::fmin(v.y, v.z));
	}
	friend inline T MaxComponent(const Vector3<T>& v) {
		return std::fmax(v.x, std::fmax(v.y, v.z));
	}
	friend inline int MaxDimension(const Vector3<T>& v) {
		return (v.x > v.y) ? (v.x > v.z ? 0 : 2) : (v.y > v.z ? 1 : 2);
	}
	friend inline int MinDimension(const Vector3<T>& v) {
		return (v.x < v.y) ? (v.x < v.z ? 0 : 2) : (v.y < v.z ? 1 : 2);
	}
	friend inline Vector3<T> min(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(std::fmin(lhs.x, rhs.x), std::fmin(lhs.y, rhs.y), std::fmin(lhs.z, rhs.z));
	}
	friend inline Vector3<T> max(const Vector3<T>& lhs, const Vector3<T>& rhs) {
		return Vector3<T>(std::fmax(lhs.x, rhs.x), std::fmax(lhs.y, rhs.y), std::fmax(lhs.z, rhs.z));
	}
	friend inline Vector3<T> swizzle(const Vector3<T>& v, int x, int y, int z) {
		return Vector3<T>(v[x], v[y], v[z]);
	}
	friend inline void CoordinateSystem(const Vector3<T>& up, Vector3<T>* forward, Vector3<T>* side) {
		if (std::abs(up.x) > std::abs(up.y)) {
			*forward = Vector3<T>(up.z, 0, -up.x) / std::sqrt(up.x * up.x + up.z * up.z);
		}
		else {
			*forward = Vector3<T>(0, -up.z, up.y) / std::sqrt(up.y * up.y + up.z * up.z);
		}
		*side = cross(up, *forward);
	}
	friend inline float distance(const Vector3<T>& v1, const Vector3<T>& v2) {
		return (v1 - v2).Length();
	}
	friend inline float distanceSquared(const Vector3<T>& v1, const Vector3<T>& v2) {
		return (v1 - v2).LengthSquared();
	}
	friend inline Vector3<T> lerp(const Vector3<T>& v1, const Vector3<T>& v2, float t)
	{
		return v1 + (v2 - v1) * t;
	}
	friend inline float length(const Vector3<T>& v1) {
		return v1.Length();
	}
	friend inline float lengthSquared(const Vector3<T>& v1) {
		return v1.LengthSquared();
	}
	friend inline Vector3<T> faceforward(const Vector3<T>& n, const Vector3<T>& v) {
		return (dot(n, v)) < 0.0f ? -n : n;
	}
public:
	T x, y, z;
};

template<typename T>
class Vector2
{
public:
	Vector2() : x(0), y(0) {}
	Vector2(T x, T y, T z) : x(x), y(y) { assert(!HasNaNs()); }
	Vector2(T scaler) :x(scaler), y(scaler) { assert(!HasNaNs()); }
	Vector2(const Vector2<T>& v) : x(v.x), y(v.y) { assert(!v.HasNaNs()); }
public:
	bool HasNaNs() const { return std::isnan(x) || std::isnan(y); }
public:
	T operator[](int index) const {
		assert(index >= 0 && index < 2);
		if (index == 0)return x;
		return y;
	}
	T& operator[](int index)
	{
		assert(index >= 0 && index < 2);
		if (index == 0)return x;
		return y;
	}
	Vector2& operator+=(const Vector2<T>& v)
	{
		x += v.x; y += v.y;
		return *this;
	}
	Vector2  operator+(const Vector2<T>& v) const
	{
		return Vector2<T>(x + v.x, y + v.y);
	}
	Vector2& operator-=(const Vector2<T>& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}
	Vector2  operator-(const Vector2<T>& v) const
	{
		return Vector2<T>(x - v.x, y - v.y);
	}
	Vector2& operator*=(const Vector2<T>& v)
	{
		x *= v.x; y *= v.y;
		return *this;
	}
	Vector2  operator*(const Vector2<T>& v) const
	{
		return Vector2<T>(x * v.x, y * v.y);
	}
	Vector2& operator/=(const Vector2<T>& v)
	{
		x /= v.x; y /= v.y;
		return *this;
	}
	Vector2  operator/(const Vector2<T>& v) const
	{
		return Vector2<T>(x / v.x, y / v.y);
	}

	Vector2& operator/=(T scaler)
	{
		assert(scaler != 0);
		T inv_scaler = (T)1 / scaler;
		x *= inv_scaler;
		y *= inv_scaler;
		return *this;
	}

	Vector2 operator/(T scaler)const
	{
		assert(scaler != 0);
		T inv_scaler = (T)1 / scaler;
		return Vector2<T>(x * inv_scaler, y * inv_scaler);
	}

	Vector2 operator-()const { return Vector2<T>(-x, -y); }
public:
	inline T LengthSquared()const {
		return x * x + y * y;
	}
	inline T Length()const
	{
		return std::sqrt(LengthSquared());
	}
	void Normalize() {
		(*this) /= Length();
	}
public:
	friend inline Vector2<T> operator+(T s, const Vector2<T> v)
	{
		return v + s;
	}
	friend inline Vector2<T> operator-(T s, const Vector2<T> v)
	{
		return Vector2<T>(s - v.x, s - v.y);
	}
	friend inline Vector2<T> operator*(T s, const Vector2<T> v)
	{
		return v * s;
	}
	friend inline Vector2<T> operator/(T s, const Vector2<T> v)
	{
		return Vector2<T>(s / v.x, s / v.y);
	}
	friend inline std::ostream& operator<<(std::ostream& os, const Vector2<T>& v) {
		os << "[ " << v.x << ", " << v.y << " ]";
		return os;
	}
	friend inline Vector2<T> abs(const Vector2<T>& v) {
		return Vector2<T>(std::abs(v.x), std::abs(v.y));
	}
	friend inline Vector2<T> floor(const Vector2<T>& v1) {
		return Vector2<T>(std::floor(v1.x), std::floor(v1.y));
	}
	friend inline Vector2<T> ceil(const Vector2<T>& v1) {
		return Vector2<T>(std::ceil(v1.x), std::ceil(v1.y));
	}
	friend inline T dot(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return lhs.x * rhs.x + lhs.y * rhs.y;
	}
	friend inline float cross(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return lhs.x * rhs.y - lhs.y * rhs.x;
	}
	friend inline Vector2<T> normalize(const Vector2<T>& v) {
		return v / v.Length();
	}

	friend inline Vector2<T> min(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(std::fmin(lhs.x, rhs.x), std::fmin(lhs.y, rhs.y));
	}
	friend inline Vector2<T> max(const Vector2<T>& lhs, const Vector2<T>& rhs) {
		return Vector2<T>(std::fmax(lhs.x, rhs.x), std::fmax(lhs.y, rhs.y));
	}
	friend inline Vector2<T> swizzle(const Vector2<T>& v, int x, int y) {
		return Vector2<T>(v[x], v[y]);
	}

	friend inline float distance(const Vector2<T>& v1, const Vector2<T>& v2) {
		return (v1 - v2).Length();
	}
	friend inline float distanceSquared(const Vector2<T>& v1, const Vector2<T>& v2) {
		return (v1 - v2).LengthSquared();
	}
	friend inline Vector2<T> lerp(const Vector2<T>& v1, const Vector2<T>& v2, float t)
	{
		return v1 + (v2 - v1) * t;
	}
	friend inline float length(const Vector2<T>& v1) {
		return v1.Length();
	}
	friend inline float lengthSquared(const Vector2<T>& v1) {
		return v1.LengthSquared();
	}
	friend inline Vector2<T> faceforward(const Vector2<T>& n, const Vector2<T>& v) {
		return (dot(n, v)) < 0.0f ? -n : n;
	}
public:
	T x, y;
};


typedef Vector3<float> float3;
typedef Vector3<int32> int3;
typedef Vector2<float> float2;
typedef Vector2<int32> int2;