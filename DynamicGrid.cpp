#include "DynamicGrid.h"
#include "Config.h"
#include "Object.h"
#include "Circle.h"
#include "Utility.h"
#include <cmath>
#include <iostream>

/*

Update: clear objects, fill objects into nodes, draw 

*/


void DynamicGrid::clear()
{
	// If nodes exist..
	if (m_node_vec.size() > 0)
	{
		// For every node..
		for (int i = 0; i < m_node_vec.size(); ++i)
		{
			// Clear its objects.
			m_node_vec[i]->clear();
		}
	}
}

void DynamicGrid::init()
{	
	numNodes = 0;
	// Clear nodes before use.
	m_node_vec.clear();

	int sqrtGrid 	= sqrt(uniGrid);
	int col 		= screen_width / sqrtGrid;
	int row 		= screen_height / sqrtGrid;

	// Split into grid
	for (int y = 0; y < screen_height; y+=row)
	{
		for (int x = 0; x < screen_width; x+=col)
		{
			m_node_vec.push_back(std::unique_ptr<Node>(new Node(Rect(Vec2(x,y),Vec2(x+col,y+row)))));
		}
	}
}

void DynamicGrid::update()
{
	// Clear node objects
	clear();

	// If objects exist..
	if (object_vec.size() > 0)
	{	
		// Go through all objects..
		for (int i = 0; i < object_vec.size(); ++i)
		{
			// Find all nodes it fits into
			for (int j = 0; j < m_node_vec.size(); ++j)
			{
				// Find out which node(s) this object fits in.
				if (m_node_vec[j]->contains(static_cast<Circle&>(*object_vec[i])))
				{
					// Insert the object into the node.
					m_node_vec[j]->insert(static_cast<Circle&>(*object_vec[i]));
				}
			}
		}
	}

}

void DynamicGrid::draw()
{	
	if (showDynaGrid)
	{	
		// If nodes exists..
		if (m_node_vec.size() > 0)
		{
			// For every node..
			for (int i = 0; i < m_node_vec.size(); ++i)
			{
				// Draw the node to screen and change color of objects in node
				m_node_vec[i]->draw();
			}
		}
	}
}

void DynamicGrid::process()
{
	if (m_node_vec.size() > 0)
	{	
		// Clear the main container
		object_vec.clear();

		for (int i = 0; i < m_node_vec.size(); ++i)
		{
			// Update pos and vel of all objects in all nodes
			m_node_vec[i]->updateObjects(0,1);

			// Put the objects back into the main container
			m_node_vec[i]->addObjectsBack();

		}
	}
}

Node::Node(const Rect& r) : m_rect(r)
{
	numNodes++;
	assignColor(m_color);
}

void Node::addObjectsBack() const
{
	for (int i = 0; i < m_object_vec.size(); ++i)
	{
		object_vec.push_back(std::unique_ptr<Object>(new Circle(static_cast<Circle&>(*m_object_vec[i]))));
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
	m_object_vec.push_back(std::unique_ptr<Object>(new Circle(b)));
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
}

void Node::updateObjects(int begin, int end)
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

DynamicGrid dynamicGrid;