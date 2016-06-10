#include "Node.h"

Node::Node(const Rect& r) : m_rect(r)
{
	numNodes++;
	assignColor(m_color);
}

void Node::addObjectsBack() const
{
	for (int i = 0; i < m_object_vec.size(); ++i)
	{
		object_vec.push_back(uptr<Object>(new Circle(static_cast<Circle&>(*m_object_vec[i]))));
	}
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


void Node::insert(const Circle& b)
{	
	// Add object to the node.
	m_object_vec.push_back(uptr<Object>(new Circle(b)));
}

void Node::draw()
{	
	// Draw the rect
	m_rect.draw();
}

void Node::clear()
{	
	// Clear the objects
	m_object_vec.clear();
	m_object_vec.shrink_to_fit();
}

void Node::updateObjects(int begin, int end)
{
	// If objects exist..
	if (m_object_vec.size() > 0)
	{
		#pragma omp parallel for
		for (int i = 0; i < m_object_vec.size(); ++i)
		{	
			for (int j = i+1; j < m_object_vec.size(); ++j)
			{
				// collision check
				if (static_cast<Circle&>(*m_object_vec[i]).collisionDetection(static_cast<Circle&>(*m_object_vec[j])))
				{
					// resolve collision
					static_cast<Circle&>(*m_object_vec[i]).resolveCollision(static_cast<Circle&>(*m_object_vec[j]));
				}
			}
			m_object_vec[i]->update();
		}
	}

	if (showDynaGrid && useDynaGrid) debug();
}

void Node::debug()
{	
	// If objects exist..
	if (m_object_vec.size() > 0)
	{
		// For every object..
		for (int i = 0; i < m_object_vec.size(); ++i)
		{
			// Change its color.
			static_cast<Circle&>(*m_object_vec[i]).changeColor(m_rect.getColor());
		}
	}
}