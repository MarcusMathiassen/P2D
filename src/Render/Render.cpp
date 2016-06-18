#include "Render.h"
#include <iostream>

void draw()
{
	for (size_t i = 0; i < object_vec.size(); ++i)
	{
		object_vec[i]->draw();
	}

	if (use_DynamicGrid && show_DynamicGrid)
	{
		spatialHash.draw();
	}

	if (use_Quadtree && show_Quadtree)
	{
		quadtree->draw();
	}
}
