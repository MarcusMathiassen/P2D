
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Quadtree.h"

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

	int x		= p1.x;
	int y 		= p1.y;
	int width	= p2.x;
	int height	= p2.y;

	int subWidth 	= (width -p1.x) * 0.5;
	int subHeight 	= (height-p1.y) * 0.5;

	//// Split into grid
	//for (int i = y; i < height; i+=subHeight)
	//{
	//	for (int j = x; j < width; j+=subWidth)
	//	{
	//		m_nodes_vec.push_back(uptr<Quadtree>(new Quadtree(m_level+1,Rect(Vec2(j,i),Vec2(j+subWidth,i+subHeight)))));
	//	}
	//}

	m_nodes_vec.push_back(uptr<Quadtree>(
		new Quadtree(m_level+1,Rect(Vec2(x,y),Vec2(subWidth,subHeight)))));

	m_nodes_vec.push_back(uptr<Quadtree>(
		new Quadtree(m_level+1,Rect(Vec2(x,y+subHeight),Vec2(subWidth,subHeight)))));

	m_nodes_vec.push_back(uptr<Quadtree>(
		new Quadtree(m_level+1,Rect(Vec2(x+subWidth,y+subHeight),Vec2(subWidth,subHeight)))));

	m_nodes_vec.push_back(uptr<Quadtree>(
		new Quadtree(m_level+1,Rect(Vec2(subWidth,y),Vec2(x+subWidth,subHeight)))));
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
	if (m_nodes_vec[0]->contains(b)) return 0;
	if (m_nodes_vec[1]->contains(b)) return 1;
	if (m_nodes_vec[2]->contains(b)) return 2;
	if (m_nodes_vec[3]->contains(b)) return 3;
	return -1;
}

void Quadtree::retrieve()
{

}

void Quadtree::addObject(const Circle& b)
{	
	m_object_vec.push_back(uptr<Object> (new Circle(b)));
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

void Quadtree::setColor(const Color& c)
{
	m_bounds.setColor(c);
}

void Quadtree::process()
{

}

void Quadtree::draw()
{
	if (show_Quadtree) {

		m_bounds.draw();

		// Tell every node to draw itself
		if (m_nodes_vec.size() > 0) {
			m_nodes_vec[0]->setColor(red);
			m_nodes_vec[1]->setColor(green);
			m_nodes_vec[2]->setColor(blue);
			m_nodes_vec[3]->setColor(white);
			m_nodes_vec[0]->draw();
			m_nodes_vec[1]->draw();
			m_nodes_vec[2]->draw();
			m_nodes_vec[3]->draw();
		}
	}
}