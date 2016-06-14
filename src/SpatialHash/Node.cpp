
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|
#include <iostream>
#include "Node.h"

Node::Node(const Rect& r) : m_rect(r)
{
	numNodes++;
	assignColor(m_color);
}

bool Node::contains(const Circle& b) const
{
	// Check if rect contains the object
	if (m_rect.contains(b))
	{
		return true;
	}
	return false;
}


void Node::insert(int i)
{
	// Add object to the node.
	m_index_vec.push_back((i));
}

void Node::draw()
{
	// Draw the rect
	m_rect.draw();
}

void Node::clear()
{
	//---------------------------------------------------------------------
	// Clears the object vector and frees any memory used by it.
	//---------------------------------------------------------------------
	m_index_vec.clear();
	m_index_vec.shrink_to_fit();
}

void Node::update()
{
	//---------------------------------------------------------------------
	// Change the color of the nodes objects to the nodes rect color.
	//---------------------------------------------------------------------

	for (size_t i = 0; i < m_index_vec.size(); ++i)
	{
		int idex = m_index_vec[i];

		for (size_t j = i+1; j < m_index_vec.size(); ++j)
		{
			int jdex = m_index_vec[j];

			// collision check
			if (static_cast<Circle&>(*object_vec[idex]).collisionDetection(static_cast<Circle&>(*object_vec[jdex])))
			{
				// resolve collision
				static_cast<Circle&>(*object_vec[idex]).resolveCollision(static_cast<Circle&>(*object_vec[jdex]));
			}
		}
	}

	if (show_DynamicGrid) debug();
}

void Node::debug()
{
	//---------------------------------------------------------------------
	// Change the color of the nodes objects to the nodes rect color.
	//---------------------------------------------------------------------

	if (object_vec.size() > 0)						// If objects exist..
	{
		for (size_t i = 0; i < m_index_vec.size(); ++i) 	// For every object..
		{
			if (m_rect.containsPos(static_cast<Circle&>(*object_vec[m_index_vec[i]])))
			{
				static_cast<Circle&>
				(*object_vec[m_index_vec[i]]).changeColor(m_rect.getColor()); // Change color.
			}
		}
	}
}