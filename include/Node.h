
//-----------------------------------------|
//  AUTHOR: MARCUS MATHIASSEN          |
//  DATE: 03.05.2016               |
//-----------------------------------------|

#pragma once

#include "Circle.h"
#include "Rect.h"
#include "Templates.h"

class Node {
 private:
  Rect m_bounds;
  vec<int> m_index;

 public:
  Node(const Rect &r);

  void insert(const int id);
  void get(vec<vec<int>> &cont);
  void draw() const;
  void color_objects();

  bool contain(const int id) const;
};
