#pragma once

#include "../Utility/Templates.h"		// vec, uptr
#include "../Utility/Color.h"			// Color class
#include "../Utility/Vec2.h"			// Vec2 class
#include "../Objects/Rectangle/Rect.h"	// Rectangle class
#include "../Objects/Circle/Circle.h"	// Circle class
#include "../Config/Config.h"			// Global vars, screen size

#define NODE_CAPACITY 25
#define NODE_MAX_DEPTH 5

class Quadtree
{
	int 				m_level;
	Rect 				m_rect;
	uptr<Quadtree> 		m_subnode[4];
	vec<int> 			m_index;

	void split();
	void insert(const int id);
	bool contain(const int id) const;
	void set_color(const Color &c);

	public:

		Quadtree(const int m_level, const Rect &m_rect);

		void update();
		void get(vec<vec<int> > &cont) const;
		void retrieve(vec<int> &cont, const Rect &rect) const;
		void draw() const;
		void reset();
}

extern Quadtree quadtree;