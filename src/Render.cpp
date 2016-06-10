#include "Render.h"

void draw()
{	
	for (int i = 0; i < object_vec.size(); ++i)
	{
		object_vec[i]->draw();
	}

	if (showDynaGrid && useDynaGrid)
	{
		dynamicGrid.draw();
	}

	quadtree.draw();
}

void debug()
{
	if (direction)
	{
		for (int i = 0; i < object_vec.size(); ++i)
		{
			static_cast<Circle&>(*object_vec[i]).debug();
		}
	}
}