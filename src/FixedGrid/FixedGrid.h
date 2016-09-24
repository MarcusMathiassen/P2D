
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

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