
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef _OBJECT_H
#define _OBJECT_H

#include "../Utility/Templates.h"	// vec, uptr

class Object
{

protected:
	int				m_index;

public:
	virtual ~Object();
	virtual void draw();
	virtual void update();
};

extern vec<uptr<Object>> object_vec;	// Our main container

#endif