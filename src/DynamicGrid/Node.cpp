
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

void Node::addObjectsBack()
{
	for (int i = 0; i < m_object_vec.size(); ++i)
	{
		object_vec.push_back(uptr<Object>
			(new Circle(static_cast<Circle&>(*m_object_vec[i]))));
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
	//---------------------------------------------------------------------
	// Clears the object vector and frees any memory used by it.
	//---------------------------------------------------------------------

	m_object_vec.clear();						// Clear the object vector.
	m_object_vec.shrink_to_fit();				// Free any memory used.
}

void Node::updateObjects(int begin, int end)
{
	//---------------------------------------------------------------------
	// Change the color of the nodes objects to the nodes rect color.
	//---------------------------------------------------------------------
	
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

	if (show_DynamicGrid) debug();
}

void Node::debug()
{	
	//---------------------------------------------------------------------
	// Change the color of the nodes objects to the nodes rect color.
	//---------------------------------------------------------------------

	if (m_object_vec.size() > 0)						// If objects exist..
	{
		for (int i = 0; i < m_object_vec.size(); ++i) 	// For every object..
		{
			static_cast<Circle&>
			(*m_object_vec[i]).changeColor(m_rect.getColor()); // Change color.
		}
	}
}