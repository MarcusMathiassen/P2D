#include "Quadtree.h"

#include <memory>
#include <iostream>
#include <vector>

#include "Config.h"
#include "Rect.h"
#include "Object.h"
#include "Circle.h"
#include "Vec2.h"

const int Quadtree::NODE_CAPACITY 	= 5;
const int Quadtree::NODE_MAX_DEPTH 	= 5;

Quadtree quadtree;

Quadtree::Quadtree()
{
	m_level = 0;
	m_bounds = Rect(Vec2(0,0),Vec2(screen_width,screen_height));
}

Quadtree::Quadtree(int level, const Rect& bounds) : m_level(level), m_bounds(bounds) {}

void Quadtree::split()
{	
	Vec2 p1 	= m_bounds.getP1();
	Vec2 p2 	= m_bounds.getP2();

	int x			= p1.x;
	int y 			= p1.y;
	int subWidth	= p2.x*0.5;
	int subHeight	= p2.y*0.5;

	Rect bottomleft		(Vec2(x,y), 					Vec2(x+subWidth, y+subHeight));
	Rect topleft		(Vec2(x, y+subHeight), 			Vec2(x+subWidth, y+subHeight));
	Rect topright		(Vec2(x+subWidth, y+subHeight), Vec2(x+subWidth, y+subHeight));
	Rect bottomright	(Vec2(x+subWidth, y), 			Vec2(x+subWidth, y+subHeight));
	
	m_nodes_vec.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, bottomleft)));
	m_nodes_vec.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, topleft)));
	m_nodes_vec.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, topright)));
	m_nodes_vec.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, bottomright)));
}

void Quadtree::clear()
{
	m_object_vec.clear();
	m_nodes_vec.clear();
}

void Quadtree::insert(const Circle& b)
{	
	//	If NODE_CAPACITY is reached AND max depth is not yet reached
	if (m_object_vec.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH)
	{	
		// If no nodes exist..
		if (m_nodes_vec.empty())
		{
			// Make some
			split();
		}

		// Get index of node
		int index = getIndex(b);

		// If object can fit
		if (index != -1)
		{
			// Insert object into node
			m_nodes_vec[index]->insert(b);
			return;
		}
	}

	// Add object to this node
	addObject(b);
} 

int Quadtree::getIndex(const Circle& b)
{	
	int index = -1;
	float vertMid = m_bounds.getP1().x + m_bounds.getP2().x *0.5; 
	float horMid  = m_bounds.getP1().y + m_bounds.getP2().y *0.5; 

	Vec2 bpos = b.getPos();
	float bx = bpos.x - b.getRadi();
	float by = bpos.y + b.getRadi();
	float bw = bpos.x + b.getRadi();
	float bh = bpos.y - b.getRadi();

	// Objects can completely fit within the top quadrants
	bool topQuad = (by > horMid && by + bh > horMid); 

	// Object can completely fit within the bottom quadrants
	bool botQuad = (by < horMid);

	// Object can completely fit within the left quadrants
	if (bx < vertMid && bx + bw < vertMid) {
		if(topQuad) {
			index = 1;
		}
		else if(botQuad) { 
			index = 0;
		}
	}

	// Object can completely fit within the right quadrants
	if (bx > vertMid) {
		if(topQuad) {
			index = 2;
		}
		else if(botQuad) {
			index = 3;
		}
	}

	return index;
}

void Quadtree::retrieve()
{

}

void Quadtree::addObject(const Circle& b)
{	
	m_object_vec.push_back(std::unique_ptr<Object> (new Circle(b)));
	//std::cout << m_object_vec.size() << " lvl " << m_level << std::endl;
}

bool Quadtree::contains(const Circle& b) const
{	
	if (m_bounds.contains(b)) return true;
	return false;
}

bool Quadtree::isFull() const
{
	if (m_object_vec.size() < NODE_CAPACITY) return false;
	return true;
}

void Quadtree::update()
{	
	// Clear the quadstrees
	clear();

	// Insert objects into the quadtree
	if (object_vec.size() > 0) {
		for (int i = 0; i < object_vec.size(); ++i) {
			insert(static_cast<Circle&>(*object_vec[i]));
		}
	}
}

void Quadtree::draw() const
{
	if (showQuadtree) {

		m_bounds.draw();

		// Tell every node to draw itself
		if (m_nodes_vec.size() > 0) {
			m_nodes_vec[0]->draw();
			m_nodes_vec[1]->draw();
			m_nodes_vec[2]->draw();
			m_nodes_vec[3]->draw();
		}
	}
}