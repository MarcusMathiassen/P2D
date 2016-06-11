
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef NODE_H
#define NODE_H

#include "../Utility/Templates.h"
#include "../Objects/Object.h"
#include "../Objects/Shapes/Rect.h"
#include "../Objects/Shapes/Circle.h"

class Node
{
	
private:

	Rect 				m_rect;
	Color 				m_color;
	vec<uptr<Object>>	m_object_vec;

public:

	Node(const Rect& r);
	bool contains(const Circle& b) const;
	void insert(const Circle& b);
	void updateObjects(int begin, int end);
	void addObjectsBack();
	void draw();
	void debug();
	void clear();
};


#endif