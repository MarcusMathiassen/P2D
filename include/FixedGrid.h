
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

// --------------------------- INCLUDES ---------------------------------

#include "Circle.h"    // Circle class
#include "Color.h"     // Color class
#include "Config.h"    // Global variables, screen size
#include "Node.h"      // Node class
#include "Rect.h"      // Rect class
#include "Templates.h" // vec, uptr
#include "Utility.h"   // assignColor()
#include <cmath>       // sqrt
#include <iostream>    // cout

// ----------------------------------------------------------------------

class FixedGrid {

private:
  vec<uptr<Node>> m_nodes;

public:
  void init();
  void update();
  void draw() const;
  void get(vec<vec<int>> &cont) const;
};

extern FixedGrid fixedgrid;
