#ifndef VEC2_H
#define VEC2_H

#include <cmath>

struct Vec2 {
  float x, y;
  Vec2();
  Vec2(const float i, const float j);
  const Vec2 operator*(const float f) const;
  const Vec2 operator+(const Vec2 &v) const;
  const Vec2 normalized() const;
};

inline float dot(const Vec2 &a, const Vec2 &b) {
  return (a.x * b.x + a.y * b.y);
}

inline float psuedo_cross(const Vec2 &a, const Vec2 &b) {
  return (a.x * b.y - a.y * b.x);
}

#endif
