
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Node.h"

Node::Node(const Rect& r) : m_rect(r)
{
	numNodes++;
	assignColor(m_color);
}

bool Node::contains(const Circle& b) const
{
	// Check if rect contains the object
	if (m_rect.contains(b)) return true;
	return false;
}

void Node::insert(int i)
{
	m_index_vec.push_back(i);
}

void Node::draw()
{
	// Draw the nodes boundaries
	m_rect.draw();
}

void Node::process()
{
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

		if (show_DynamicGrid)
		{

			//---------------------------------------------------------------------
			// Change the color of the nodes objects to the nodes rect color.
			//---------------------------------------------------------------------

			if (m_rect.containsPos(static_cast<Circle&>(*object_vec[idex])))
			{
				static_cast<Circle&>(*object_vec[idex]).changeColor(m_rect.getColor());
			}
		}
	}

	// Clear the vector for next frame
	m_index_vec.clear();
	m_index_vec.shrink_to_fit();
}
