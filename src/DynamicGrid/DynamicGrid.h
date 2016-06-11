
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef DYNAMICGRID_H
#define DYNAMICGRID_H

// --------------------------- INCLUDES ---------------------------------

#include <cmath>						// sqrt
#include "Node.h"						// Node class
#include "../Config.h"					// Global variables, screen size
#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Utility.h"			// assignColor()
#include "../Objects/Object.h"			// Object class
#include "../Objects/Shapes/Circle.h"	// Circle class
#include "../Objects/Shapes/Rect.h"		// Rect class	

// ----------------------------------------------------------------------


class DynamicGrid
{

private:

	vec<uptr<Node>>		m_node_vec;

public:

	void init();
	void clear();
	void update();
	void process();
	void draw();

};

extern DynamicGrid dynamicGrid;

#endif