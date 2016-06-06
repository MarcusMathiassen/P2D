#include "Render.h"
#include "Object.h"
#include "Quadtree.h"

void draw()
{	
	for (int i = 0; i < object_v.size(); ++i) {
		object_v[i]->draw();
	}

	quadtree.draw();
}