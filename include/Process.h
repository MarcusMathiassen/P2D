
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

#include "Config.h" 				// Ballcol
#include "Templates.h" 			// vec
#include "FixedGrid.h"			// fixedgrid
#include "Quadtree.h"			// quadtree
#include "Circle.h"		// circle

void update();
void Calc(const vec<vec<int> > &cont, size_t begin, const size_t end);