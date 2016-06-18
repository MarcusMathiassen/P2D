
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef NODE_H
#define NODE_H

#include "../Utility/Templates.h"
#include "../Objects/Object.h"
#include "../Objects/Rectangle/Rect.h"
#include "../Objects/Circle/Circle.h"

class Node
{

private:

	Rect 					m_rect;
	Color 					m_color;

	vec<int> 				m_index_vec;

public:

	Node(const Rect& r);
	bool contains(const Circle& b) const;
	void insert(int i);

	void process();
	void draw();
};


#endif