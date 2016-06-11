
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Process.h"


void Calc(int begin, int end) {
	for (int i = begin; i < end; i++) {		

		if (ballCol)
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

	if (object_vec.size() > 0) {		// If there are objects..

		if (use_Quadtree)				// If Quadtrees are active.
		{
			quadtree.update();
			quadtree.process();
			return;
		}

		if (use_DynamicGrid)			// If DynamicGrid is active.
		{	
			dynamicGrid.update();
			dynamicGrid.process();
			return;
		}

		if (use_pThread && !use_Quadtree){

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
		}
	}
}