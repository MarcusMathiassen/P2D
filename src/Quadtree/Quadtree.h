#ifndef QUADTREE_H
#define QUADTREE_H	

#include "../Utility/Templates.h"				// vec, uptr
#include "../Utility/Color.h"					// Color class
#include "../Utility/Vec2.h"					// Vec2 class
#include "../Objects/Object.h"					// Object class
#include "../Objects/Shapes/Rect.h"				// Rect class
#include "../Objects/Shapes/Circle.h"			// Circle class
#include "../Config.h"							// Global vars, screen size

class Quadtree {

private:

	int 								m_level;
	Rect 								m_bounds;
	vec<uptr<Quadtree>>					m_nodes_vec;
	vec<uptr<Object>> 					m_object_vec;
	
	static const int 					NODE_CAPACITY;
	static const int 					NODE_MAX_DEPTH;

public:

	Quadtree();
	Quadtree(int level, const Rect& bounds);

	void split();
	void clear();
	void retrieve();
	void insert(const Circle& b);
	
	void testSplit();
	void addObject(const Circle& b);
	int getIndex(const Circle& b);
	bool contains(const Circle& b) const;
	bool isFull() const;
	void setColor(const Color& c);

	void update();
	void draw();
};

extern Quadtree quadtree;

#endif