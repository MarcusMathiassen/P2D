#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float i, float j) : x(i), y(j) {}
Vec2 Vec2::operator *(float f) { return Vec2(x*f,y*f);}
Vec2 Vec2::operator +(const Vec2& v) { return Vec2(x+v.x,y+v.y);}

Vec2 Vec2::normalized(){float mg=sqrt(x*x+y*y); return Vec2(x/mg,y/mg);}