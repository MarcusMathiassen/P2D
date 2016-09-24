
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"

void Calc(const size_t begin, const size_t end)
{
	for (size_t k = begin; k < end; ++k)
	{
		for (size_t i = 0; i < cont[k].size(); ++i)
		{
			for (size_t j = i+1; j < cont[k].size(); ++j)
			{
				if (object_vec[cont[k][i]]->collision_detection(*object_vec[cont[k][j]]))
				{
					object_vec[cont[k][i]]->collision_resolve(*object_vec[cont[k][j]]);
				}
			}
		}
	}
}

void update()
{
	if (object_vec.size() > 0)
	{
		if (ballCol)
		{
			vec<vec<int> > 	cont;

			if (use_quadtree) 		{ quadtree.update(); 	quadtree.get(cont); }
			else if (use_fixedgrid) { fixedgrid.update(); 	fixedgrid.get(cont); }

			// If we´re using collision optimizations
			if (use_quadtree || use_fixedgrid) Calc(0, cont.size());

			// Brute force
			else
			{
				for (size_t i = 0; i < object_vec.size(); ++i)
				{
					for (size_t j = i+1; j < object_vec.size(); ++j)
					{
						if (object_vec[i]->collision_detection(*object_vec[j]))
						{
							object_vec[i]->collision_resolve(*object_vec[j]);
						}
					}
				}
			}
		}

		// Update each objects position
		for (auto& object: object_vec) object->update();
	}
}