#ifndef VEC2_H
#define VEC2_H

#include <cmath>

struct Vec2 {
	float x,y;
	Vec2();
	Vec2(float i, float j);
	Vec2 operator *(float f);
	Vec2 operator +(const Vec2& v);
	Vec2 normalized();
};

inline float dot(const Vec2& a, const Vec2& b)
{
	return (a.x*b.x + a.y*b.y);
}

inline float psuedo_cross(const Vec2& a, const Vec2& b)
{
	return (a.x*b.y - a.y*b.x);
}

#endif