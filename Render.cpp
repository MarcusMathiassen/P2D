#include "Render.h"

#include "Ball.h"
#include "Config.h"
#include "Quadtree.h"

#include <GL/glew.h>
#include <cmath>

void draw()
{	
	int numBalls = ball_vec.size();

	for (int i = 0; i < numBalls; ++i) {
		ball_vec[i]->draw();
	}
	debug();
}

void debug() {

	// Draw quadtrees
	if (drawQuadtrees) {
		quadtree.draw();
	}

	// Draws lines showing the direction and velocity of each ball.
	if (direction) {

		int numBalls = ball_vec.size();

		for (int i = 0; i < numBalls; ++i) {

			float x 	= ball_vec[i]->getPosX();
			float y 	= ball_vec[i]->getPosY();
			float vx 	= ball_vec[i]->getVelX();
			float vy 	= ball_vec[i]->getVelY();

			float distance 	= sqrt(vx*vx+vy*vy);
			float angle 	= atan2(vy,vx);	

			float ny 	= y + distance * sin(angle);
			float nx 	= x + distance * cos(angle);

			float r 	= ball_vec[i]->getColR();
			float g 	= ball_vec[i]->getColG();
			float b 	= ball_vec[i]->getColB();

			glColor3ub(r,g,b);
			glBegin(GL_LINES);
			glVertex2d(x,y);
			glVertex2d(vx+nx,vy+ny);
			glEnd();
		}
	}
}