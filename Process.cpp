#include "Process.h"

#include "Quadtree.h"
#include "Config.h"
#include "Object.h"

#include <cmath>
#include <thread>
#include <vector>

void Calc(int begin, int end) {

	for (int i = begin; i < end; i++) 
	{		
		// updates its pos and vel.
		object_v[i]->update();
	}
}

void update() {

	// Update the quadtrees
	quadtree.update();

	// If there are objects..
	if (object_v.size() > 0) {

		// Number of balls per thread
		int parts = object_v.size() / numThreads;

		// Our thread container
		std::vector<std::thread> t(numThreads);
		
		Calc(parts*numThreads, object_v.size());
		for (int i = 0; i < numThreads; ++i) {
			t[i] = std::thread(Calc, parts * i, parts * (i+1));
		}
		for (int i = 0; i < numThreads; ++i) {
			t[i].join();
		}

	} else Calc(0,object_v.size());
}