//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "FixedGrid.h"			// Declaration

FixedGrid fixedgrid;

void FixedGrid::init()
{
	//-----------------------------------------------------------------------------------
	// The nodes are cleared and given an element in the grid.
	//-----------------------------------------------------------------------------------

	m_nodes.clear();
	m_nodes.shrink_to_fit();

	float sqrtGrid 	= sqrt(uniGrid);
	int col 		= screen_width/sqrtGrid;
	int row 		= screen_height/sqrtGrid;

	for (int y = 0; y < screen_height; y+=row)
	{
		for (int x = 0; x < screen_width; x+=col)
		{
			Rect bounds(Vec2(x,y),Vec2(x+col,y+row));
			m_nodes.emplace_back(std::make_unique<Node>(bounds));
		}
	}
}

void FixedGrid::update()
{
	//-----------------------------------------------------------------------------------
	// Goes through every node and fills it with objects from the
	// main-container, any object that fits within the nodes boundaries will
	// be added to the nodes object-container.
	//-----------------------------------------------------------------------------------

	for (const auto& object: object_vec)
	{
		for (const auto& node: m_nodes)
		{
			if (node->contain(*object))
			{
				node->insert(*object);
			}

			// Color the objects with the color of the node.
			node->color_objects();
		}
	}
}

void FixedGrid::get(vec<vec<int>>& cont) const
{
	for (const auto& node: m_nodes)
	{
		node->get(cont);
	}
}

void FixedGrid::draw() const
{
	//-----------------------------------------------------------------------------------
	// Draws the nodes boundaries to screen and colors the objects within
	// each node with the nodes color.
	//-----------------------------------------------------------------------------------

	for (const auto& node: m_nodes)
	{
		node->draw();
	}
}