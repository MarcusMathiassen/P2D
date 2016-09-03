#ifndef QUADTREE_H
#define QUADTREE_H

#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Color.h"			// Color class
#include "../Utility/Vec2.h"			// Vec2 class
#include "../Objects/Rectangle/Rect.h"	// Rectangle class
#include "../Objects/Circle/Circle.h"	// Circle class
#include "../Config/Config.h"			// Global vars, screen size

#define NODE_CAPACITY   25
#define NODE_MAX_DEPTH  5

class Quadtree
{
	
private:

	int 				m_level;
	Rect 				m_bounds;
	uptr<Quadtree>		m_subnode[4];
	vec<int>			m_index;

	void split();
	void insert(const Circle& object);
	bool contain(const Circle& object) const;
	void set_color(const Color& c);

public:

	Quadtree(int level, const Rect& bounds);

	void update();
	void get(vec<vec<int> >& cont) const;
	void draw() const;
	void reset();
};

extern Quadtree quadtree;

#endif