#include "Process.h"


void Calc(int begin, int end) {
	for (int i = begin; i < end; i++) {		

		if (ballCol && !useQuadtree)
		for (int j = i+1; j < object_vec.size(); j++) {
	
			// collision check
			if (static_cast<Circle&>(*object_vec[i]).collisionDetection(static_cast<Circle&>(*object_vec[j]))) {
	
				// resolve collision
				static_cast<Circle&>(*object_vec[i]).resolveCollision(static_cast<Circle&>(*object_vec[j]));
			}
		}

		// updates its pos and vel.
		object_vec[i]->update();
	}
}

void update() {

	int numObj = (int)object_vec.size();

	// If there are objects..
	if (numObj > 0) {

		// Update the quadtrees (NOT YET FINISHED)
		quadtree.update();

		// Update the dynamic grid (NOT YET FINISHED)
		if (useDynaGrid)
		{	
			dynamicGrid.update();
			dynamicGrid.process();
			return;
		}

		if (use_pThread && !useQuadtree){

			if (numThreads == 0) { Calc(0,numObj); return; }
			// Number of balls per thread
			int parts = numObj / numThreads;
		
			// Our thread container
			vec<std::thread> t(numThreads);
			
			Calc(parts*numThreads, numObj);
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
			for (int i = 0; i < numObj; ++i) {		
				if (ballCol && !useQuadtree)
				for (int j = i+1; j < numObj; ++j) {
					// collision check
					if (static_cast<Circle&>(*object_vec[i]).collisionDetection(static_cast<Circle&>(*object_vec[j]))) {
						// resolve collision
						static_cast<Circle&>(*object_vec[i]).resolveCollision(static_cast<Circle&>(*object_vec[j]));
					}
				}
				// updates its pos and vel.
				object_vec[i]->update();
			}
			return;
		#endif
	}
}