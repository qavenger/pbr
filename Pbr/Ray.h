#pragma once
#include "Vector.h"
class Medium;
class Ray
{
public:
	Ray();
	Ray(const float3& o, const float3& d, float tMax = INFINITY, float time = 0, const Medium* medium = nullptr);
	float3 operator()(float t)const;
public:
	float3 o, d;
	mutable float tMax;
	float time;
	const Medium* medium;
};

class RayDifferential : public Ray
{
public:
	RayDifferential():hasDifferentials(false) {}
	RayDifferential(const float3& o, const float3& d, float tMax = INFINITY, float time = 0, const Medium* medium = nullptr);
	RayDifferential(const Ray& ray);
public:
	void ScaleDifferentials(float s);
public:
	bool hasDifferentials;
	float3 rxOrigin, ryOrigin;
	float3 rxDirection, ryDirection;
};