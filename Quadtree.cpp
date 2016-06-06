#include "Quadtree.h"

#include <iostream>
#include <vector>
#include <GL/glew.h>

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
	m_bounds = Rect(Vec2(0,0),Vec2(WINDOW_WIDTH,WINDOW_HEIGHT));
}

Quadtree::Quadtree(int level, const Rect& bounds) : m_level(level), m_bounds(bounds) {}

void Quadtree::split()
{	
	Vec2 p1 	= m_bounds.getP1();
	Vec2 p2 	= m_bounds.getP2();

	int x	= p1.x;
	int y 	= p1.y;
	int w	= p2.x;
	int h	= p2.y;

	// Bottom left
	Rect zero	(Vec2(w*0.5,	h*0.5),
				 Vec2(x,		y));
	// bottom right
	Rect one	(Vec2(w*0.5,	h*0.5),
				 Vec2(w,		y));
	// Top left
	Rect two	(Vec2(w*0.5,	h*0.5),	
				Vec2(x,			h));
	// top right
	Rect three	(Vec2(w*0.5,	h*0.5),
				 Vec2(w,		h));
	
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, one)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, zero)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, two)));
	m_nodes_v.push_back(std::unique_ptr<Quadtree>(new Quadtree(m_level+1, three)));
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

	if (m_nodes_v[0]->contains(b)) {
				std::cout << "0\n";
	}
	if (m_nodes_v[1]->contains(b)) {
				std::cout << "1\n";
	} 
	if (m_nodes_v[2]->contains(b)) {
				std::cout << "2\n";
	} 
	if (m_nodes_v[3]->contains(b)) {
				std::cout << "3\n";
	} 

	// Object can completely fit within the left quadrants
	if (bx < vertMid && bx + bw < vertMid) {
		if(topQuad) {
			index = 2;
		}
		else if(botQuad) { 
			index = 1;
		}
	}

	// Object can completely fit within the right quadrants
	if (bx > vertMid) {
		if(topQuad) {
			index = 3;
		}
		else if(botQuad) {
			index = 0;
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
			insert(dynamic_cast<Circle&>(*object_v[i]));
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