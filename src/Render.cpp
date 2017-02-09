#include "Render.h"

void draw() {
  for (auto &object : object_vec) object->draw();
  if (debug_mode) debug();
}

void debug() {
  if (use_fixedgrid) fixedgrid.draw();
  if (use_quadtree) quadtree.draw();
}
