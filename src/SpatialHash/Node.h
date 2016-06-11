
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

	Rect 					m_rect;
	Color 					m_color;

	vec<int>				m_index_vec;			// Index of objects

public:

	Node(const Rect& r);
	bool contains(const Circle& b) const;
	void insert(int i);
	void update();
	void draw();
	void debug();
	void clear();
};


#endif