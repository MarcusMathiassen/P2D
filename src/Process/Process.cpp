
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"

vec<vec<int>> cont;

void Calc(size_t begin, size_t end) {

	for (size_t k = begin; k < end; ++k) {

		for (size_t i = 0; i < cont[k].size(); ++i)
		{
			for (size_t j = i+1; j < cont[k].size(); ++j)
			{
				if (object_vec[cont[k][i]]->collision_detection(*object_vec[cont[k][j]]))
				{
					// Save K,I,J for resolve later
					//object_vec[cont[k][i]]->collision_resolve(*object_vec[cont[k][j]]);
				}
			}
		}
	}
}

void update() {

	if (object_vec.size() > 0) {		// If there are objects..

		cont.clear();

		if (use_Quadtree && ballCol)			// If Quadtrees are active.
		{

			quadtree.update();
			//quadtree.get(cont);
			quadtree.process();
		}

		if (use_DynamicGrid && ballCol)			// If DynamicGrid is active.
		{
			spatialHash.update();
			spatialHash.process();
		}


		//int parts = cont.size() / numThreads;
		//vec<std::thread> t(numThreads);
//
		//Calc(parts*numThreads, cont.size());
		//for (int i = 0; i < numThreads; ++i) {
		//	t[i] z= std::thread(Calc, parts * i, parts * (i+1));
		//}
		//for (int i = 0; i < numThreads; ++i) {
		//	t[i].join();
		//}

		//for (size_t k = 0; k < cont.size(); ++k)
		//{
		//	for (size_t i = 0; i < cont[k].size(); ++i)
		//	{
		//		for (size_t j = i+1; j < cont[k].size(); ++j)
		//		{
		//			if (object_vec[cont[k][i]]->collision_detection(*object_vec[cont[k][j]]))
		//			{
		//				object_vec[cont[k][i]]->collision_resolve(*object_vec[cont[k][j]]);
		//			}
		//		}
		//	}
		//}

		#pragma omp parallel for
		for (size_t i = 0; i < object_vec.size(); ++i)
		{
			object_vec[i]->update();
		}
	}
}