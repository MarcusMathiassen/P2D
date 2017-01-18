
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#pragma once

#include "Templates.h"
#include "Rect.h"
#include "Circle.h"

class Node
{

private:

	Rect 					m_bounds;
	vec<int> 			m_index;

public:

	Node(const Rect& r);

	void insert(const int id);
	void get(vec<vec<int> >& cont);
	void draw() const;
	void color_objects();

	bool contain(const int id) const;
};
