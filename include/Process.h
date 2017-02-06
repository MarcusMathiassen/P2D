
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

#include "Circle.h"    // circle
#include "Config.h"    // Ballcol
#include "FixedGrid.h" // fixedgrid
#include "Quadtree.h"  // quadtree
#include "Templates.h" // vec

void update();
void process_segment(int begin, int end);
void Calc(const vec<vec<int>> &cont, size_t begin, const size_t end);
