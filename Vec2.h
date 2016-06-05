#ifndef VEC2_H
#define VEC2_H

struct Vec2 {
	float x,y;
	Vec2();
	Vec2(float i, float j);
	void operator *(float f);
};

#endif