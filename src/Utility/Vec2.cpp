#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(const float i, const float j) : x(i), y(j) {}
const Vec2 Vec2::operator *(const float f) const { return Vec2(x*f,y*f);}
const Vec2 Vec2::operator +(const Vec2& v) const { return Vec2(x+v.x,y+v.y);}
const Vec2 Vec2::normalized() const {const float mg=sqrt(x*x+y*y); return Vec2(x/mg,y/mg);}