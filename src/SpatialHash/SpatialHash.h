
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef SPATIALHASH_H
#define SPATIALHASH_H

// --------------------------- INCLUDES ---------------------------------

#include <iostream>						// cout
#include <cmath>						// sqrt
#include "./Node/Node.h"				// Node class
#include "../Config/Config.h"			// Global variables, screen size
#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Utility.h"			// assignColor()
#include "../Utility/Color.h"			// Color class
#include "../Objects/Circle/Circle.h"	// Circle class
#include "../Objects/Rectangle/Rect.h"	// Rect class

// ----------------------------------------------------------------------

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