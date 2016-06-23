
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef PROCESS_H
#define PROCESS_H


#include <thread>
#include "../Config/Config.h"
#include "../Utility/Templates.h"
#include "../Utility/getTime64.h"
#include "../SpatialHash/SpatialHash.h"
#include "../Quadtree/Quadtree.h"
#include "../Objects/Circle/Circle.h"

void update();
void Calc(size_t begin, size_t end);
void copy_vec(vec<Circle>& a,const vec<uptr<Circle>>& b);
#endif