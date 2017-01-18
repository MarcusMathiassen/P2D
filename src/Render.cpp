#include "Render.h"

void draw()
{
	for (auto& object: object_vec) object->draw();

	if (debug_mode) debug();
}

void debug()
{
	if (use_fixedgrid) 	fixedgrid.draw();
	if (use_quadtree) 	quadtree.draw();
}

/*
bool collision_detection(const GameObject& a, const GameObject& b)
{
	// Setup local variables of GameObject a
	const glm::vec2 ap{a.pos};
	const int ar{a.radi};

	// Setup local variables of GameObject b
	const glm::vec2 bp{b.pos};
	const int ar{b.radi};

	// basic square collision check
	if (ap.x - ar < bx + br && ap.x + ar > bx - br &&
			ap.y - ar < by + br && ap.y + ar > by - br)
	{
		// Circle collision check
		const float dx = bx - ap.x;
    const float dy = by - ap.y;
    const float sumRadius = ar + br;
    const float sqrRadius = sumRadius * sumRadius;

    const float distSqr = (dx * dx) + (dy * dy);

    if (distSqr <= sqrRadius) return true;
  }
  return false;
}

*/
