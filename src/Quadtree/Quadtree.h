
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef QUADTREE_H
#define QUADTREE_H

#include "../Utility/Templates.h"				// vec, uptr
#include "../Utility/Color.h"					// Color class
#include "../Utility/Vec2.h"					// Vec2 class
#include "../Objects/Rectangle/Rect.h"			// Rectangle class
#include "../Objects/Circle/Circle.h"			// Circle class
#include "../Config/Config.h"					// Global vars, screen size

#define NODE_CAPACITY   50
#define NODE_MAX_DEPTH  6

class Quadtree
{

private:

	int 				m_level;
	Rect 				m_bounds;
	uptr<Quadtree>		m_subnode[4];
	vec<int>			m_index;

	void split();
	void insert(const Circle& object);
	bool contains(const Circle& object) const;

public:

	Quadtree();
	Quadtree(int level, const Rect& bounds);

	void update();
	void process() const;
	void reset();
	void draw() const;
};

extern Quadtree quadtree;

#endif