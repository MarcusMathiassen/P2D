#include "Process.h"

#include "Quadtree.h"
#include "Config.h"
#include "Object.h"

#include <cmath>
#include <thread>
#include <vector>

void Calc(int begin, int end) {
	for (int i = begin; i < end; i++) {		

		if (ballCol && !useQuadtree)
		for (int j = i+1; j < object_v.size(); j++) {
	
			// collision check
			if (static_cast<Circle&>(*object_v[i]).collisionDetection(static_cast<Circle&>(*object_v[j]))) {
	
				// resolve collision
				static_cast<Circle&>(*object_v[i]).resolveCollision(static_cast<Circle&>(*object_v[j]));
			}
		}

		// updates its pos and vel.
		object_v[i]->update();
	}
}

void update() {

	// If there are objects..
	if (object_v.size() > 0) {
		int numObj = (int)object_v.size();
		// Update the quadtrees (NOT YET FINISHED)
		quadtree.update();

		if (use_pThread && !useQuadtree){

			if (numThreads == 0) { Calc(0,numObj); return; }
			// Number of balls per thread
			int parts = numObj / numThreads;
		
			// Our thread container
			std::vector<std::thread> t(numThreads);
			
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
					if (static_cast<Circle&>(*object_v[i]).collisionDetection(static_cast<Circle&>(*object_v[j]))) {
						// resolve collision
						static_cast<Circle&>(*object_v[i]).resolveCollision(static_cast<Circle&>(*object_v[j]));
					}
				}
				// updates its pos and vel.
				object_v[i]->update();
			}
			return;
		#endif
	}
}