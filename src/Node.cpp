
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Node.h"
#include <iostream>

Node::Node(const Rect &r) : m_bounds{r} {}

bool Node::contain(const int id) const { return m_bounds.contain(id); }

void Node::insert(const int id) { m_index.emplace_back(id); }

void Node::draw() const {
  // Draw the nodes boundaries
  m_bounds.draw();
}

void Node::color_objects() {
  // Color the balls in the same color as the boundaries
  for (const auto &id : m_index) {
    object_vec[id]->set_temp_color(m_bounds.get_color());
  }
}

void Node::get(vec<vec<int>> &cont) {
  cont.emplace_back(m_index);
  m_index.clear();
  m_index.shrink_to_fit();
}
