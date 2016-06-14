
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Object.h"
Object::~Object() {}
void Object::draw() {}
void Object::update() {}

vec<uptr<Object>> object_vec; // Our main container