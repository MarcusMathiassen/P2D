
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "SpatialHash.h"			// Declaration

SpatialHash spatialHash;

void SpatialHash::init()
{	
	// ---------------------------------------------------------------------
	// The nodes are cleared and given an element in the grid.
	// ---------------------------------------------------------------------

	numNodes = 0;								// Set number of nodes to 0.

	m_node_vec.clear();							// Clear the node vector.
	m_node_vec.shrink_to_fit();					// Free any memory used.

												// Split screen into grid..
	float sqrtGrid 	= sqrt(uniGrid);			
	int col 		= screen_width/sqrtGrid;
	int row 		= screen_height/sqrtGrid;

	for (int y = 0; y < screen_height; y+=row)
	{
		for (int x = 0; x < screen_width; x+=col)
		{
			m_node_vec.push_back(uptr<Node>
				(new Node(Rect(Vec2(x,y),Vec2(x+col,y+row)))));
		}
	}
}

void SpatialHash::update()
{
	//---------------------------------------------------------------------
	//	Clears all nodes and their objects. (If we didn´t do this, 
	//	each nodes object-container would increase in size each frame, 
	//	basically leaking memory.)
	//---------------------------------------------------------------------

	if (m_node_vec.size() > 0)						// If nodes exist..
	{
		#ifdef BENCHMARK
		int b =  GetTimeMs64();
		#endif

		for (size_t i = 0; i < m_node_vec.size(); ++i)	// Go through all nodes..
		{
			m_node_vec[i]->clear();					// Clear their objects.
		}

		#ifdef BENCHMARK
		int a =  GetTimeMs64()-b;
		std::cout << " - Clear nodes:     " << a << " ms" << std::endl;
		#endif
	}


	//---------------------------------------------------------------------
	// Goes through every node and fills it with objects from the 
	// main-container, any object that fits within the nodes boundaries will
	// be added to the nodes object-container.
	//---------------------------------------------------------------------

	#ifdef BENCHMARK
	int b =  GetTimeMs64();
	#endif

	for (size_t i = 0; i < object_vec.size(); ++i)
	{
		for (size_t j = 0; j < m_node_vec.size(); ++j)
		{
			if (m_node_vec[j]->contains(static_cast<Circle&>(*object_vec[i])))
			{
				m_node_vec[j]->insert(static_cast<Circle&>(*object_vec[i]).getIndex());
			}
		}
	}

	#ifdef BENCHMARK
	int a =  GetTimeMs64()-b;
	std::cout << " - SpatialHash: update():    " << a << " ms" << std::endl;
	#endif
	

}

void SpatialHash::process()
{
	//---------------------------------------------------------------------
	// Checks if any objects in the node collide with eachother, and if so, 
	// resolves those collision.
	//---------------------------------------------------------------------

	if (m_node_vec.size() > 0)					// If nodes exists..
	{	

		#ifdef BENCHMARK
		int b =  GetTimeMs64();
		#endif

		#pragma omp parallel for
		for (size_t i = 0; i < m_node_vec.size(); ++i)	// Go through all nodes..
		{
			m_node_vec[i]->update();		// Check collisons
		}
		
		#ifdef BENCHMARK
		int a =  GetTimeMs64()-b;
		std::cout << " - SpatialHash process():   " << a << " ms" << std::endl;
		#endif
	}
}

void SpatialHash::draw()
{	
	//---------------------------------------------------------------------
	// Draws the nodes boundaries to screen and colors the objects within 
	// each node with the nodes color.
	//---------------------------------------------------------------------

	if (m_node_vec.size() > 0)						// If nodes exists..
	{
		for (size_t i = 0; i < m_node_vec.size(); ++i) // Go through all nodes..
		{
			m_node_vec[i]->draw();					// Draw their boundaries.
		}
	}
}