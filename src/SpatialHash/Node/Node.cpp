
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

void Node::get(vec<vec<int>>& cont)
{
	cont.emplace_back(m_index_vec);
	m_index_vec.clear();
	m_index_vec.shrink_to_fit();
}