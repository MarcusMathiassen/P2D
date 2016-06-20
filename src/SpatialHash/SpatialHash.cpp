//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "SpatialHash.h"			// Declaration

SpatialHash spatialHash;

void SpatialHash::init()
{
	//-----------------------------------------------------------------------------------
	// The nodes are cleared and given an element in the grid.
	//-----------------------------------------------------------------------------------

	m_node_vec.clear();
	m_node_vec.shrink_to_fit();

	float sqrtGrid 	= sqrt(uniGrid);
	int col 		= screen_width/sqrtGrid;
	int row 		= screen_height/sqrtGrid;

	for (int y = 0; y < screen_height; y+=row)
	{
		for (int x = 0; x < screen_width; x+=col)
		{
			Rect bounds(Vec2(x,y),Vec2(x+col,y+row));
			m_node_vec.emplace_back(std::make_unique<Node>(bounds));
		}
	}
}

void SpatialHash::update()
{
	//-----------------------------------------------------------------------------------
	// Goes through every node and fills it with objects from the
	// main-container, any object that fits within the nodes boundaries will
	// be added to the nodes object-container.
	//-----------------------------------------------------------------------------------

	for (const auto& object: object_vec)
	{
		for (const auto& node: m_node_vec)
		{
			if (node->contains(*object))
			{
				node->insert(*object);
			}
		}
	}
}

void SpatialHash::get(vec<vec<int>>& cont) const
{
	for (const auto& node: m_node_vec)
	{
		node->get(cont);
	}
}

void SpatialHash::draw() const
{
	//-----------------------------------------------------------------------------------
	// Draws the nodes boundaries to screen and colors the objects within
	// each node with the nodes color.
	//-----------------------------------------------------------------------------------

	for (const auto& node: m_node_vec)
	{
		node->draw();
	}
}