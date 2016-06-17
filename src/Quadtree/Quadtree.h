
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>								// cout
#include "../Utility/Templates.h"				// vec, uptr
#include "../Utility/Color.h"					// Color class
#include "../Utility/Vec2.h"					// Vec2 class
#include "../Utility/getTime64.h"				// BENCHMARK
#include "../Objects/Object.h"					// Object class
#include "../Objects/Shapes/Rect.h"				// Rect class
#include "../Objects/Shapes/Circle.h"			// Circle class
#include "../Config.h"							// Global vars, screen size

#define NODE_CAPACITY   100
#define NODE_MAX_DEPTH  6


class Quadtree
{

private:

	int 								m_level;
	Rect 								m_bounds;

	Quadtree*							m_subnode[4];
	vec<int>							m_index;

public:

	Quadtree();
	Quadtree(int level, const Rect& bounds);
	~Quadtree();

	void reset();
	void split();
	void insert(const Circle& b);

	void update();
	void process();
	void draw() const;

	bool contains(const Circle& b) const;
	void setColor(const Color& c);
};

extern Quadtree quadtree;

#endif