
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Node.h"

Node::Node(const Rect& r) : m_rect{r} {}

bool Node::contains(const Circle& object) const
{
	// Check if rect contains the Object
	if (m_rect.contains(object)) return true;
	return false;
}

void Node::insert(const Circle& object)
{
	m_index_vec.emplace_back(object.get_index());
}

void Node::draw() const
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
			if (object_vec[idex]->collision_detection(*object_vec[jdex]))
			{
				// resolve collision
				object_vec[idex]->collision_resolve(*object_vec[jdex]);
			}
		}
	}

	// Clear the vector for next frame
	m_index_vec.clear();
	m_index_vec.shrink_to_fit();
}