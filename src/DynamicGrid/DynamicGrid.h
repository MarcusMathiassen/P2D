
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


/*

	HOW THE DYNAMIC GRID WORKS:

	---------------------------------------------------------------------

	PROGRAM START AND EVERY SCREEN RESIZE: 

	init():
	---------------------------------------------------------------------
	The nodes are cleared and given an element in the grid.
	---------------------------------------------------------------------


	EACH FRAME(in order): 
	
	clear(): 
	---------------------------------------------------------------------
	Clears all nodes and their objects. (If we didn´t do this, each nodes
	object-container would increase in size each frame, basically 
	leaking memory.)
	---------------------------------------------------------------------

	update(): 
	---------------------------------------------------------------------
	Goes through every node and fills it with objects from the 
	main-container, any object that fits within the nodes boundaries will
	be added to the nodes object-container.
	---------------------------------------------------------------------

	process(): 
	---------------------------------------------------------------------
	Checks if any objects in the node collide with eachother, and if so, 
	resolves those collision.
	---------------------------------------------------------------------

	draw():	
	---------------------------------------------------------------------
	Draws the nodes boundaries to screen and colors the objects within 
	each node with the nodes color.
	---------------------------------------------------------------------

*/


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