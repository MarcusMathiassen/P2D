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
const int Quadtree::NODE_MAX_DEPTH 	= 10;

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

	int x	= p1.x;
	int y 	= p1.y;
	int w	= p2.x*0.5;
	int h	= p2.y*0.5;

	// Bottom left
	Rect bottomleft	(Vec2(x,	y),
                     Vec2(w,	h));
	// bottom right
	Rect topleft	(Vec2(x+w,	y),
                     Vec2(w,	h));
	// Top left
	Rect topright	(Vec2(x,	y+h),
                     Vec2(w,	h));
	// top right
	Rect bottomright(Vec2(x+w,	y+h),
                     Vec2(w,	h));
	
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, bottomleft)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, topleft)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, topright)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, bottomright)));
}

void Quadtree::clear()
{
	m_object_v.clear();
	m_nodes_v.clear();
}

void Quadtree::insert(const Circle& b)
{	
	// if nodes exist..
	if (m_nodes_v.size() > 0) {
		int index = getIndex(b);

		// And they contain our object
		if (index != -1) {
			m_nodes_v[index]->insert(b);
			return;
		}
	}

	addObject(b);

	if (m_object_v.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH) {
		if (m_nodes_v.size() == 0) {
			split();
		}
	}
} 

int Quadtree::getIndex(const Circle& b)
{	
	int index = -1;
	float vertMid = m_bounds.getP1().x + m_bounds.getP2().x *0.5; 
	float horMid  = m_bounds.getP1().y + m_bounds.getP2().y *0.5; 

	Vec2 bpos = b.getPos();
	float bx = bpos.x - b.getRadi();
	float by = bpos.y - b.getRadi();
	float bw = bpos.x + b.getRadi();
	float bh = bpos.y + b.getRadi();

	// Objects can completely fit within the top quadrants
	bool topQuad = (by < horMid && by + bh < horMid); 

	// Object can completely fit within the bottom quadrants
	bool botQuad = (by > horMid);

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
	m_object_v.push_back(std::unique_ptr<Object> (new Circle(b)));
	//std::cout << m_object_v.size() << " lvl " << m_level << std::endl;
}

bool Quadtree::contains(const Circle& b) const
{	
	if (m_bounds.contains(b.getPos())) return true;
	return false;
}

bool Quadtree::isFull() const
{
	if (m_object_v.size() < NODE_CAPACITY) return false;
	return true;
}

void Quadtree::update()
{	
	// Clear the quadstrees
	clear();

	// Insert objects into the quadtree
	if (object_v.size() > 0) {
		for (int i = 0; i < object_v.size(); ++i) {
			insert(static_cast<Circle&>(*object_v[i]));
		}
	}
}

void Quadtree::draw() const
{
	if (drawQuadtrees) {

		m_bounds.draw();

		// Tell every node to draw itself
		if (m_nodes_v.size() > 0) {
			m_nodes_v[0]->draw();
			m_nodes_v[1]->draw();
			m_nodes_v[2]->draw();
			m_nodes_v[3]->draw();
		}
	}
}