#include "Render.h"

void draw()
{
	for (size_t i = 0; i < object_vec.size(); ++i)
	{
		object_vec[i]->draw();
	}

	if (debug_mode) debug();
}

void debug()
{
	if (use_fixedgrid) 	fixedgrid.draw();
	if (use_quadtree) 	quadtree.draw(); 
}