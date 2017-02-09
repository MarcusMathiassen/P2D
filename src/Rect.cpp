
//-----------------------------------------|
//  AUTHOR: MARCUS MATHIASSEN          |
//  DATE: 03.05.2016               |
//-----------------------------------------|

#include "Rect.h"

Rect::Rect() : min(Vec2(0, 0)), max(Vec2(0, 0)) {}

Rect::Rect(const Vec2 &a, const Vec2 &b) : min(a), max(b) {
  assignColor(m_color);
  if (use_fixedgrid) uniCol++;
}

void Rect::draw() const {
  glColor3ub(m_color.r, m_color.g, m_color.b);
  glLineWidth(1.0);
  glBegin(GL_LINE_LOOP);
  glVertex2f(min.x + 1, min.y + 1);
  glVertex2f(min.x + 1, max.y - 1);
  glVertex2f(max.x - 1, max.y - 1);
  glVertex2f(max.x - 1, min.y + 1);
  glEnd();
}

bool Rect::contain(const int id) const {
  Vec2 o = object_vec[id]->get_pos();
  float r = object_vec[id]->get_radi();

  //  basic square collision check
  if (o.x - r < max.x && o.x + r > min.x && o.y - r < max.y &&
      o.y + r > min.y) {
    return true;
  }

  return false;
}

bool Rect::contain_rect(const Rect &r) const {
  Vec2 rmin = r.get_min();
  Vec2 rmax = r.get_max();

  //  basic square collision check
  if (rmax.x < max.x && rmin.x > min.x && rmax.y < max.y && rmin.y > min.y) {
    return true;
  }

  return false;
}

bool Rect::contain_pos(const Vec2 &v) const {
  if (v.x < min.x || v.x > max.x) return false;
  if (v.y < min.y || v.y > max.y) return false;

  return true;
}

Vec2 Rect::get_min() const { return min; }
Vec2 Rect::get_max() const { return max; }
Color Rect::get_color() const { return m_color; }
void Rect::set_color(const Color &c) { m_color = c; }
