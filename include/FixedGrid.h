
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

// --------------------------- INCLUDES ---------------------------------

#include <iostream>						// cout
#include <cmath>						// sqrt
#include "Node.h"				// Node class
#include "Config.h"			// Global variables, screen size
#include "Templates.h"		// vec, uptr
#include "Utility.h"			// assignColor()
#include "Color.h"			// Color class
#include "Circle.h"	// Circle class
#include "Rect.h"	// Rect class

// ----------------------------------------------------------------------

class FixedGrid
{

private:

	vec<uptr<Node> >		m_nodes;

public:

	void init();
	void update();
	void draw() const;
	void get(vec<vec<int> >& cont) const;

};

extern FixedGrid fixedgrid;