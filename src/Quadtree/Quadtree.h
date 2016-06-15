
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


const int NODE_CAPACITY     = 25;
const int NODE_MAX_DEPTH  	= 6;

class Quadtree {

private:

	int 								m_level;
	Rect 								m_bounds;

	vec<uptr<Quadtree>>					m_nodes_vec;

	vec<int>							m_index_vec;

public:

	Quadtree();
	Quadtree(int level, const Rect& bounds);

	void init();
	void split();
	void insert(const Circle& b);

	void update();
	void process();
	void draw();

	bool contains(const Circle& b) const;
	void setColor(const Color& c);
	void setRect(const Rect& r);
};

extern Quadtree quadtree;

#endif