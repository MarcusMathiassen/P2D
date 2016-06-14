
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef SPATIALHASH_H
#define SPATIALHASH_H

// --------------------------- INCLUDES ---------------------------------

#include <iostream>						// cout
#include <cmath>						// sqrt
#include "Node.h"						// Node class
#include "../Config.h"					// Global variables, screen size
#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Utility.h"			// assignColor()
#include "../Utility/getTime64.h"		// BENCHMARK
#include "../Utility/Color.h"			// Color class
#include "../Objects/Object.h"			// Object class
#include "../Objects/Shapes/Circle.h"	// Circle class
#include "../Objects/Shapes/Rect.h"		// Rect class	

// ----------------------------------------------------------------------

// How to run:
/*
	
	init() every time the grid is changed or the window is resized.
	update() every frame
	draw() every frame	
*/


class SpatialHash
{

private:

	vec<uptr<Node>>		m_node_vec;

public:

	void init();
	void update();
	void process();
	void draw();

};

extern SpatialHash spatialHash;

#endif