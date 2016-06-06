#include "Render.h"
#include "Object.h"
#include "Quadtree.h"

void draw()
{	
	for (int i = 0; i < object_v.size(); ++i) {
		object_v[i]->draw();
	}

	quadtree.draw();

	debug();
}

void debug()
{
	// Draws lines showing the direction and velocity.
	if (direction) {
		for (int i = 0; i < object_v.size(); ++i) {
			static_cast<Circle&>(*object_v[i]).debug();
		}
	}
}