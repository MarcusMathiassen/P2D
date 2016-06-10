#include "DynamicGrid.h"			// Declaration

/*

	HOW THE DYNAMIC GRID WORKS:

	---------------------------------------------------------------------

	PROGRAM START AND EVERY SCREEN RESIZE: 

	init():
	---------------------------------------------------------------------
	The nodes are cleared and given an element in the grid.
	---------------------------------------------------------------------


	EACH FRAME(in order run): 
	
	clear(): 
	---------------------------------------------------------------------
	Clears all nodes and their objects. (If we didn´t do this, each nodes 	object-container would increase in size each frame, basically leaking memory.)
	---------------------------------------------------------------------

	update(): 
	---------------------------------------------------------------------
	Goes through every node and fills it with objects from the 
	main-container, any object that fits within the nodes boundaries will 
	be added to the nodes object-container.
	---------------------------------------------------------------------

	process(): 
	---------------------------------------------------------------------
	Checks if any objects in the node collide with eachother, and if so, resolves that collision.
	---------------------------------------------------------------------

	draw():	
	---------------------------------------------------------------------
	Draws the nodes boundaries to screen and colors the objects within 
	each node with the nodes color.
	---------------------------------------------------------------------

*/


void DynamicGrid::clear()
{
	//---------------------------------------------------------------------
	//	Clears all nodes and their objects. (If we didn´t do this, 
	//	each nodes object-container would increase in size each frame, 
	//	basically leaking memory.)
	//---------------------------------------------------------------------

	if (m_node_vec.size() > 0)						// If nodes exist..
	{
		for (int i = 0; i < m_node_vec.size(); ++i)	// Go through all nodes..
		{
			m_node_vec[i]->clear();					// Run their clear().
		}
	}
}

void DynamicGrid::init()
{	
	numNodes = 0;
	
	// Clear nodes before use.
	m_node_vec.clear();
	m_node_vec.shrink_to_fit();

	int sqrtGrid 	= sqrt(uniGrid);
	int col 		= screen_width / sqrtGrid;
	int row 		= screen_height / sqrtGrid;

	// Split into grid
	for (int y = 0; y < screen_height; y+=row)
	{
		for (int x = 0; x < screen_width; x+=col)
		{
			m_node_vec.push_back(uptr<Node>(new Node(Rect(Vec2(x,y),Vec2(x+col,y+row)))));
		}
	}
}

void DynamicGrid::update()
{
	// Clear node objects
	clear();

	// If objects exist..
	if (object_vec.size() > 0)
	{	
		// Go through all objects..
		for (int i = 0; i < object_vec.size(); ++i)
		{
			// Find all nodes it fits into
			for (int j = 0; j < m_node_vec.size(); ++j)
			{
				// Find out which node(s) this object fits in.
				if (m_node_vec[j]->contains(static_cast<Circle&>(*object_vec[i])))
				{
					// Insert the object into the node.
					m_node_vec[j]->insert(static_cast<Circle&>(*object_vec[i]));
				}
			}
		}
	}

}

void DynamicGrid::draw()
{	
	if (showDynaGrid)
	{	
		// If nodes exists..
		if (m_node_vec.size() > 0)
		{
			// For every node..
			for (int i = 0; i < m_node_vec.size(); ++i)
			{
				// Draw the node to screen and change color of objects in node
				m_node_vec[i]->draw();
			}
		}
	}
}

void DynamicGrid::process()
{
	if (m_node_vec.size() > 0)
	{	
		// Clear the main container
		object_vec.clear();
		// Free memory used
		object_vec.shrink_to_fit();

		for (int i = 0; i < m_node_vec.size(); ++i)
		{
			// Update pos and vel of all objects in all nodes
			m_node_vec[i]->updateObjects(0,1);

			// Put the objects back into the main container
			m_node_vec[i]->addObjectsBack();

		}
	}
}

DynamicGrid dynamicGrid;