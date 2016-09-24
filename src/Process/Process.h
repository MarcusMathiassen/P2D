
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

#include "../Config/Config.h" 				// Ballcol
#include "../Utility/Templates.h" 			// vec
#include "../FixedGrid/FixedGrid.h"			// fixedgrid
#include "../Quadtree/Quadtree.h"			// quadtree
#include "../Objects/Circle/Circle.h"		// circle

void update();
void Calc(const size_t begin, const size_t end);