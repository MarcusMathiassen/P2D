
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef PROCESS_H
#define PROCESS_H


#include <thread>

#include "../Config/Config.h"
#include "../Utility/Templates.h"
#include "../SpatialHash/SpatialHash.h"
#include "../Quadtree/Quadtree.h"
#include "../Objects/Circle/Circle.h"

void update();
void Calc(int begin, int end);

#endif