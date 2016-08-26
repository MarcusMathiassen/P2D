
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Node.h"
#include <iostream>

Node::Node(const Rect& r) : m_bounds{r} {}

bool Node::contain(const Circle& object) const
{
	if (m_bounds.contain(object)) return true;
	return false;
}

void Node::insert(const Circle& object)
{
	m_index.emplace_back(object.get_index());
}

void Node::draw() const
{
	// Draw the nodes boundaries
	m_bounds.draw();
}

void Node::color_objects()
{
	// Color the balls in the same color as the boundaries
	for (const auto& id: m_index)
	{
		object_vec[id]->set_temp_color(m_bounds.get_color());
	}
}

void Node::get(vec<vec<int>>& cont)
{
	cont.emplace_back(m_index);
	m_index.clear();
	m_index.shrink_to_fit();
}