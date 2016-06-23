
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"

vec<vec<int>> cont;
vec<int>	  temp;
std::mutex lockit;

void copy_vec(vec<Circle>& a,const vec<uptr<Circle>>& b)
{
	a.reserve(b.size());
	for (const auto& bb: b)
	{
		a.emplace_back(*bb);
	}
}

void Calc(size_t begin, size_t end)
{
	vec<Circle> temp_vec;

	copy_vec(temp_vec,object_vec);

	for (size_t k = begin; k < end; ++k)
	{
		for (size_t i = 0; i < cont[k].size(); ++i)
		{
			for (size_t j = i+1; j < cont[k].size(); ++j)
			{
				if (temp_vec[cont[k][i]].collision_detection(temp_vec[cont[k][j]]))
				{
					temp.emplace_back(cont[k][i]);
					temp.emplace_back(cont[k][j]);
				}
			}
		}
	}
}

void update()
{
	if (object_vec.size() > 0)
	{
		temp.clear();
		temp.shrink_to_fit();

		if (ballCol)
		{
			if (use_Quadtree)
			{
				cont.clear();
				cont.shrink_to_fit();
				quadtree.update();
				quadtree.get(cont);
			}

			if (use_DynamicGrid)
			{
				cont.clear();
				cont.shrink_to_fit();
				spatialHash.update();
				spatialHash.get(cont);
			}
		}


		// Collision detections
		int parts = cont.size() / numThreads;
		vec<std::thread> t(numThreads);
		Calc(parts*numThreads, cont.size());
		for (int i = 0; i < numThreads; ++i)
		{
			t[i] = std::thread(Calc, parts * i, parts * (i+1));
		}
		for (int i = 0; i < numThreads; ++i)
		{
			t[i].join();
		}

		// Resolve all collisions.
		for (size_t i = 0; i < temp.size(); i+=2)
		{
			object_vec[temp[i]]->collision_resolve(*object_vec[temp[i+1]]);
		}

		#pragma omp parallel for
		for (size_t i = 0; i < object_vec.size(); ++i)
		{
			object_vec[i]->update();
		}
	}
}