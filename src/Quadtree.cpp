#include "Quadtree.h"
#include <iostream>

Quadtree quadtree(0, Rect(Vec2(0, 0), Vec2(screen_width, screen_height)));

Quadtree::Quadtree(const int m_level, const Rect &m_rect)
    : m_level(m_level),
      m_rect(m_rect),
      m_subnode{nullptr, nullptr, nullptr, nullptr} {
  m_index.reserve(NODE_CAPACITY);
}

void Quadtree::update() {
  //----------------------------------------------------------------
  // Clear the quadtree and insert it with objects.
  //----------------------------------------------------------------

  m_index.clear();
  m_index.shrink_to_fit();

  m_subnode[0] = nullptr;
  m_subnode[1] = nullptr;
  m_subnode[2] = nullptr;
  m_subnode[3] = nullptr;

  for (const auto &object : object_vec) {
    insert(object->get_index());
  }
}

void Quadtree::split() {
  //----------------------------------------------------------------
  // Create subnodes and gives each its own quadrant.
  //----------------------------------------------------------------

  Vec2 min = m_rect.get_min();
  Vec2 max = m_rect.get_max();

  int x = min.x;
  int y = min.y;
  int width = max.x - min.x;
  int height = max.y - min.y;

  int w = width * 0.5;
  int h = height * 0.5;

  Rect SW(Vec2(x, y), Vec2(x + w, y + h));
  Rect SE(Vec2(x + w, y), Vec2(x + width, y + h));
  Rect NW(Vec2(x, y + h), Vec2(x + w, y + height));
  Rect NE(Vec2(x + w, y + h), Vec2(x + width, y + height));

  m_subnode[0] = std::make_unique<Quadtree>(m_level + 1, SW);
  m_subnode[1] = std::make_unique<Quadtree>(m_level + 1, SE);
  m_subnode[2] = std::make_unique<Quadtree>(m_level + 1, NW);
  m_subnode[3] = std::make_unique<Quadtree>(m_level + 1, NE);
}

void Quadtree::insert(const int id) {
  //----------------------------------------------------------------
  // [1] Insert object into subnodes.
  // [2] If split, insert THIS nodes objects into the subnodes.
  // [3] Add object to this node.
  //----------------------------------------------------------------

  // If this subnode has split..
  if (m_subnode[0] != nullptr) {
    // Find the subnodes that contain it and insert it there.
    if (m_subnode[0]->contain(id)) m_subnode[0]->insert(id);
    if (m_subnode[1]->contain(id)) m_subnode[1]->insert(id);
    if (m_subnode[2]->contain(id)) m_subnode[2]->insert(id);
    if (m_subnode[3]->contain(id)) m_subnode[3]->insert(id);

    return;
  }

  // Add object to this node
  m_index.emplace_back(id);  // [3]

  // If it has NOT split..and NODE_CAPACITY is reached and we are not at MAX
  // LEVEL..
  if (m_index.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH) {
    // Split into subnodes.
    split();

    // Go through all this nodes objects..
    for (const auto &index : m_index)  // [2]
    {
      // Go through all newly created subnodes..
      for (const auto &subnode : m_subnode) {
        // If they contain the objects..
        if (subnode->contain(index)) {
          // Insert the object into the subnode
          subnode->insert(index);
        }
      }
    }

    // Remove all indexes from THIS node
    m_index.clear();
    m_index.shrink_to_fit();
  }
}

void Quadtree::get(vec<vec<int>> &cont) const {
  //----------------------------------------------------------------
  // [1] Find the deepest level node.
  // [2] If there are indexes, add to container.
  //----------------------------------------------------------------

  // If this subnode has split..
  if (m_subnode[0] != nullptr)  // [1]
  {
    // Continue down the tree
    m_subnode[0]->get(cont);
    m_subnode[1]->get(cont);
    m_subnode[2]->get(cont);
    m_subnode[3]->get(cont);

    return;
  }

  // Insert indexes into our container
  if (m_index.size() != 0) cont.emplace_back(m_index);  // [2]
}

void Quadtree::retrieve(vec<int> &cont, const Rect &rect) const {
  //----------------------------------------------------------------
  // [1] Find the deepest level node.
  // [2] If there are indexes, add to container.
  //----------------------------------------------------------------

  // If this subnode has split..
  if (m_subnode[0] != nullptr)  // [1]
  {
    // Continue down the tree
    if (m_subnode[0]->contain_rect(rect)) m_subnode[0]->retrieve(cont, rect);
    if (m_subnode[1]->contain_rect(rect)) m_subnode[1]->retrieve(cont, rect);
    if (m_subnode[2]->contain_rect(rect)) m_subnode[2]->retrieve(cont, rect);
    if (m_subnode[3]->contain_rect(rect)) m_subnode[3]->retrieve(cont, rect);

    return;
  }

  // Add all indexes to our container
  for (const auto &index : m_index) cont.emplace_back(index);
}

void Quadtree::reset() {
  //----------------------------------------------------------------
  // Sets bounds to the screens bounds and clears the quadtrees.
  //----------------------------------------------------------------

  m_rect = Rect(Vec2(0, 0), Vec2(screen_width, screen_height));
  m_index.clear();
  m_index.shrink_to_fit();

  m_subnode[0] = nullptr;
  m_subnode[1] = nullptr;
  m_subnode[2] = nullptr;
  m_subnode[3] = nullptr;
}

void Quadtree::draw() const {
  //----------------------------------------------------------------
  // [1] Draw this nodes boundaries.
  // [2] Draw subnodes boundaries.
  //----------------------------------------------------------------

  if (m_subnode[0] != nullptr)  // [2]
  {
    // Set color of each subnode
    m_subnode[0]->set_color(pastel_red);
    m_subnode[1]->set_color(pastel_gray);
    m_subnode[2]->set_color(pastel_orange);
    m_subnode[3]->set_color(pastel_pink);

    // Continue down the tree
    m_subnode[0]->draw();
    m_subnode[1]->draw();
    m_subnode[2]->draw();
    m_subnode[3]->draw();

    return;
  }

  // Color the balls in the same color as the boundaries
  for (const auto &id : m_index) {
    object_vec[id]->set_temp_color(m_rect.get_color());
  }

  // Only draw the nodes with objects in them.
  if (m_index.size() != 0) m_rect.draw();  // [1]
                                           // m_rect.draw(); // draw them all '
}

bool Quadtree::contain(const int id) const { return m_rect.contain(id); }

bool Quadtree::contain_rect(const Rect &rect) const {
  return m_rect.contain_rect(rect);
}

void Quadtree::set_color(const Color &c) { m_rect.set_color(c); }
