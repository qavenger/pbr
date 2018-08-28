#pragma once
#include "MathDef.h"
#include "Vector.h"
template<typename T>
class BoundingBox3D
{
public:
	BoundingBox3D() {
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = Vector3<T>(maxNum, maxNum, maxNum);
		pMax = Vector3<T>(minNum, minNum, minNum);
	}
	BoundingBox3D(const Vector3<T>& p) : pMin(p), pMax(p){}
	BoundingBox3D(const Vector3<T>& p1, const Vector3<T>& p2):
		pMin(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y), std::fmin(p1.z, p2.z)),
		pMax(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y), std::fmax(p1.z, p2.z))
	{}
public:
	const Vector3<T>& operator[](int index)const {
		assert(index >= 0 && index < 2);
		if (index == 0)return pMin;
		return pMax;
	}
	Vector3<T> operator[](int index) {
		assert(index >= 0 && index < 2);
		if (index == 0)return pMin;
		return pMax;
	}
	Vector3<T> Corner(int corner)const {
		return Vector3<T>(
			(*this)[corner & 1].x,
			(*this)[corner & 2 ? 1:0].y,
			(*this)[corner & 4 ? 1:0].z
			);
	}
	Vector3<T> Diagonal()const {
		return pMax - pMin;
	}

	T SurfaceArea()const
	{
		Vector3<T> d = Diagonal();
		return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
	}

	T Volume()const
	{
		Vector3<T> d = Diagonal();
		return d.x * d.y * d.z;
	}

	int MaximumExtent()const
	{
		Vector3<T> d = Diagonal();
		if (d.x > d.y && d.x > d.z) return 0;
		else if (d.y > d.z) return 1;
		else return 2;
	}

	Vector3<T> Lerp(const Vector3<T>& t)const
	{
		return Vector3<T>(
			lerp(pMin.x, pMax.x, t.x),
			lerp(pMin.y, pMax.y, t.y),
			lerp(pMin.z, pMax.z, t.z)
			);
	}

	Vector3<T> Offset(const Vector3<T>& p)const
	{
		Vector3<T> o = p - pMin;
		//o /= pMax - pMin;

		if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
		if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
		if (pMax.z > pMin.z) o.z /= pMax.z - pMin.z;
		return o;
	}

	void BoundingSphere(Vector3<T>* center, float* radius)const
	{
		*center = (pMin + pMax) / 2;
		*radius = Inside(*center, *this) ? distance(*center, pMax) : 0;
	}

public:
	friend inline BoundingBox3D<T> Union(const BoundingBox3D<T>& b, const Vector3<T>& p)
	{
		return BoundingBox3D<T>(
			Vector3<T>(
				std::fmin(b.pMin.x, p.x),
				std::fmin(b.pMin.y, p.y),
				std::fmin(b.pMin.z, p.z)),
			Vector3<T>(
				std::fmax(b.pMax.x, p.x),
				std::fmax(b.pMax.y, p.y),
				std::fmax(b.pMax.z, p.z)));
	}
	friend inline BoundingBox3D<T> Union(const BoundingBox3D<T>& b1, const BoundingBox3D<T>& b2)
	{
		return BoundingBox3D<T>(
			Vector3<T>(
				std::fmin(b1.pMin.x, b2.pMin.x),
				std::fmin(b1.pMin.y, b2.pMin.y),
				std::fmin(b1.pMin.z, b2.pMin.z)),
			Vector3<T>(
				std::fmax(b1.pMax.x, b2.pMax.x),
				std::fmax(b1.pMax.y, b2.pMax.y),
				std::fmax(b1.pMax.z, b2.pMax.z)));
	}
	friend inline BoundingBox3D<T> Intersect(const BoundingBox3D<T>& b1, const BoundingBox3D<T>& b2)
	{
		return BoundingBox3D<T>(
			Vector3<T>(
				std::fmax(b1.pMin.x, b2.pMin.x),
				std::fmax(b1.pMin.y, b2.pMin.y),
				std::fmax(b1.pMin.z, b2.pMin.z)),
			Vector3<T>(
				std::fmin(b1.pMax.x, b2.pMax.x),
				std::fmin(b1.pMax.y, b2.pMax.y),
				std::fmin(b1.pMax.z, b2.pMax.z)));
	}
	friend inline bool Overlap(const BoundingBox3D<T>& b1, const BoundingBox3D<T>& b2)
	{
		bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
		bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
		bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
		return (x && y && z);
	}
	friend inline bool Inside(const Vector3<T>& p, const BoundingBox3D<T>& b)
	{
		return
			(p.x >= b.pMin.x && p.x <= b.pMax.x) &&
			(p.y >= b.pMin.y && p.y <= b.pMax.y) &&
			(p.z >= b.pMin.z && p.z <= b.pMax.z);
	}
	friend inline bool InsideExclusive(const Vector3<T>& p, const BoundingBox3D<T>& b)
	{
		return
			(p.x > b.pMin.x && p.x < b.pMax.x) &&
			(p.y > b.pMin.y && p.y < b.pMax.y) &&
			(p.z > b.pMin.z && p.z < b.pMax.z);
	}
	template<typename U>
	friend inline BoundingBox3D<T> Expand(const BoundingBox3D<T>& b, U delta)
	{
		return BoundingBox3D<T>(
			b.pMin - Vector3<T>(delta),
			b.pMax + Vector3<T>(delta));
	}

public:
	Vector3<T> pMin, pMax;
};

template<typename T>
class BoundingBox2D
{
public:
	BoundingBox2D() {
		T minNum = std::numeric_limits<T>::lowest();
		T maxNum = std::numeric_limits<T>::max();
		pMin = Vector2<T>(maxNum, maxNum);
		pMax = Vector2<T>(minNum, minNum);
	}
public:
	Vector2<T> pMin, pMax;
};

typedef BoundingBox3D<float> AABB3f;
typedef BoundingBox3D<int32> AABB3i;
typedef BoundingBox2D<float> AABB2f;
typedef BoundingBox2D<int32> AABB2i;
