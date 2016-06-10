#include "Vec2.h"

Vec2::Vec2() : x(0), y(0) {}
Vec2::Vec2(float i, float j) : x(i), y(j) {}
void Vec2::operator *(float f) { x *= f; y *= f; }