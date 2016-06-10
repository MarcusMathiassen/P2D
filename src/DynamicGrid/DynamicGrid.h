#ifndef DYNAMICGRID_H
#define DYNAMICGRID_H

#include <cmath>						// sqrt

#include "Node.h"						// Node class
#include "../Config.h"					// Global variables, screen size
#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Utility.h"			// assignColor()
#include "../Objects/Object.h"			// Object class
#include "../Objects/Shapes/Circle.h"	// Circle class
#include "../Objects/Shapes/Rect.h"		// Rect class			


class DynamicGrid
{

private:

	vec<uptr<Node>>		m_node_vec;		// Contains our nodes.

public:

	void insert();						// Insert objects into nodes.
	void init();						// Setup grid.
	void draw();						// Draw nodes boundaries.
	void clear();						// Clears all nodes.
	void update();						// Inserts 
	void process();

};

extern DynamicGrid dynamicGrid;

#endif