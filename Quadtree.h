#ifndef QUADTREE_H
#define QUADTREE_H	

#include <memory>
#include "Rect.h"
#include "Object.h"
#include "Circle.h"
#include "Config.h"
#include <vector>

class Quadtree {

private:

	int 										m_level;
	Rect 										m_bounds;
	std::vector<std::unique_ptr<Quadtree>>		m_nodes_v;
	std::vector<std::unique_ptr<Object>> 		m_object_v;
	
	static const int 							NODE_CAPACITY;
	static const int 							NODE_MAX_DEPTH;

public:

	Quadtree();
	Quadtree(int level, const Rect& bounds);

	void split();
	void clear();
	void retrieve();
	void insert(const Circle& b);
	
	void addObject(const Circle& b);
	int getIndex(const Circle& b);
	bool contains(const Circle& b) const;
	bool isFull() const;

	void update();
	void draw() const;
};

extern Quadtree quadtree;

#endif