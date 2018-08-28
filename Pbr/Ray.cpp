#include "Ray.h"

Ray::Ray() : d(1, 0, 0), tMax(INFINITY), time(0), medium(nullptr)
{
}

Ray::Ray(const float3 & o, const float3 & d, float tMax, float time, const Medium * medium) :
	o(o), d(d), tMax(tMax), time(time), medium(medium)
{
}

float3 Ray::operator()(float t) const
{
	return o+d*t;
}

RayDifferential::RayDifferential(const float3 & o, const float3 & d, float tMax, float time, const Medium * medium):
	Ray(o, d, tMax, time, medium), hasDifferentials(false)
{
}

RayDifferential::RayDifferential(const Ray & ray):
	Ray(ray), hasDifferentials(false)
{

}

void RayDifferential::ScaleDifferentials(float s)
{
	rxOrigin = o + (rxOrigin - o) * s;
	ryOrigin = o + (ryOrigin - o) * s;
	rxDirection = d + (rxDirection - d) * s;
	ryDirection = d + (ryDirection - d) * s;
}
