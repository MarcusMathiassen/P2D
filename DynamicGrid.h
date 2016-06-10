#ifndef FIXEDGRID_H
#define FIXEDGRID_H

#include <memory>
#include <vector>

#include "Object.h"
#include "Circle.h"
#include "Rect.h"

class Node;


class DynamicGrid
{
private:
	std::vector<std::unique_ptr<Node>> 			m_node_vec;

public:
	void insert();
	void init();
	void draw();
	void clear();
	void update();
	void process();
};



class Node
{
private:
	Rect 										m_rect;
	Color 										m_color;
	std::vector<std::unique_ptr<Object>> 		m_object_vec;

public:
	Node(const Rect& r);
	bool contains(const Circle& b) const;
	void insert(const Circle& b);
	void updateObjects(int begin, int end);
	void addObjectsBack() const;
	void draw();
	void debug();
	void clear();
};


extern DynamicGrid dynamicGrid;

#endif