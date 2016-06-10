#ifndef _OBJECT_H
#define _OBJECT_H

#include "../Utility/Templates.h"	// vec, uptr

struct Object
{
	virtual void draw() const;
	virtual void update();	
};

extern vec<uptr<Object>> object_vec;	// Our main container

#endif