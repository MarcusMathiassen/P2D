
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"

vec<vec<int> > 	cont;

void copy_vec(vec<Circle>& a,const vec<uptr<Circle> >& b)
{
	a.reserve(b.size());
	for (const auto& bb: b)
	{
		a.emplace_back(*bb);
	}
}

void Calc(size_t begin, size_t end)
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
			cont.clear();
			cont.shrink_to_fit();

			if (use_quadtree)
			{
				quadtree.update();
				quadtree.get(cont);
				Calc(0, cont.size());
			}
			else if (use_fixedgrid)
			{
				fixedgrid.update();
				fixedgrid.get(cont);
				Calc(0, cont.size());
			}
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

		for (size_t i = 0; i < object_vec.size(); ++i)
		{
			object_vec[i]->update();
		}
	}
}