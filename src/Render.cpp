#include "Render.h"
#include <iostream>

void draw()
{	

	debug();
	
	for (size_t i = 0; i < object_vec.size(); ++i)
	{
		object_vec[i]->draw();
	}

	if (show_DynamicGrid)
	{
		spatialHash.draw();
	}

	if (show_Quadtree)
	{
		quadtree.draw();
	}
}

void debug()
{
	if (direction)
	{
		for (size_t i = 0; i < object_vec.size(); ++i)
		{
			static_cast<Circle&>(*object_vec[i]).debug();
		}
	}

}