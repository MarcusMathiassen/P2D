
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef RENDER_H
#define RENDER_H

#include "./Objects/Object.h"					// Object class
#include "./Quadtree/Quadtree.h"				// Quadtree class
#include "Config.h"								// Global vars, screen size
#include "./SpatialHash/SpatialHash.h"			// SpatialHash class

void draw();
void debug();

#endif