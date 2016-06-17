
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"


void Calc(int begin, int end) {

	for (int i = begin; i < end; i++) {
		if (ballCol)
		for (size_t j = i+1; j < object_vec.size(); j++) {

			// collision check
			if (static_cast<Circle&>(*object_vec[i]).collision_detection(static_cast<Circle&>(*object_vec[j]))) {

				// resolve collision
				static_cast<Circle&>(*object_vec[i]).collision_resolve(static_cast<Circle&>(*object_vec[j]));
			}
		}

		// updates its pos and vel.
		object_vec[i]->update();
	}
}

void update() {

	if (object_vec.size() > 0) {		// If there are objects..

		if (use_Quadtree && ballCol)			// If Quadtrees are active.
		{
			quadtree->update();

			#ifdef BENCHMARK
			int b =  GetTimeMs64();
			#endif

			quadtree->process();

			#ifdef BENCHMARK
			int a =  GetTimeMs64()-b;
			std::cout << " - Quadtree process():   " << a << " ms" << std::endl;
			#endif

			#pragma omp parallel for
			for (size_t i = 0; i < object_vec.size(); ++i)
			{
				object_vec[i]->update();
			}
			return;
		}

		if (use_DynamicGrid && ballCol)			// If DynamicGrid is active.
		{
			spatialHash.update();
			spatialHash.process();

			#pragma omp parallel for
			for (size_t i = 0; i < object_vec.size(); ++i)
			{
				object_vec[i]->update();
			}
			return;
		}

		if (use_pThread){

			if (numThreads == 0) { Calc(0,object_vec.size()); return; }
			// Number of balls per thread
			int parts = object_vec.size() / numThreads;

			// Our thread container
			vec<std::thread> t(numThreads);

			Calc(parts*numThreads, object_vec.size());
			for (int i = 0; i < numThreads; ++i) {
				t[i] = std::thread(Calc, parts * i, parts * (i+1));
			}
			for (int i = 0; i < numThreads; ++i) {
				t[i].join();
			}
			return;
		}

		// Use OpenMP if defined in the config
		#ifdef OPENMP
			#pragma omp parallel for
			for (size_t i = 0; i < object_vec.size(); ++i) {
				if (ballCol)
				for (size_t j = i+1; j < object_vec.size(); ++j) {
					// collision check
					if (static_cast<Circle&>(*object_vec[i]).collision_detection(static_cast<Circle&>(*object_vec[j]))) {
						// resolve collision
						static_cast<Circle&>(*object_vec[i]).collision_resolve(static_cast<Circle&>(*object_vec[j]));
					}
				}
				// updates its pos and vel.
				object_vec[i]->update();
			}
		#endif
	}
}