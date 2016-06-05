#include "Process.h"

#include "Quadtree.h"
#include "Config.h"
#include "Ball.h"
#include "Rect.h"

#include <cmath>
#include <thread>
#include <vector>
#include <iostream>

void CalcBall(int begin, int end) {

	for (int i = begin; i < end; i++) 
	{		
		// Ball updates its pos and vel.
		ball_vec[i]->update();

		if(gravForce) {
			for (int j = 0; j < ball_vec.size(); ++j) {
				CalculateGravity(*ball_vec[i], *ball_vec[j]);
			} 
		}

		if (borderCol)	borderCollision(i);
		if (ballCol) 	CircleCollisionCheck(i);
	}
}

void update() {

	// Update the quadtrees
	quadtree.update();

	if (ball_vec.size() > 0) {

		// Number of balls per thread
		int parts = ball_vec.size() / numThreads;

		// Our thread container
		std::vector<std::thread> t(numThreads);
		
		CalcBall(parts*numThreads, ball_vec.size());
		for (int i = 0; i < numThreads; ++i) {
			t[i] = std::thread(CalcBall, parts * i, parts * (i+1));
		}
		for (int i = 0; i < numThreads; ++i) {
			t[i].join();
		}

	} else CalcBall(0,ball_vec.size());
}

void borderCollision(int i) {

	float x 	= ball_vec[i]->getPosX();
	float y 	= ball_vec[i]->getPosY();
	float vx 	= ball_vec[i]->getVelX();
	float vy 	= ball_vec[i]->getVelY();
	float r 	= ball_vec[i]->getRadi();

	if (x <= r && vx < 0) {		
		ball_vec[i]->setPosX(r); 
		ball_vec[i]->setVelX(-vx);		
	}

	if (x >= WINDOW_WIDTH-r && vx > 0) { 
		ball_vec[i]->setPosX(WINDOW_WIDTH-r); 
		ball_vec[i]->setVelX(-vx);
	}

	if (y <= r && vy < 0) {
		ball_vec[i]->setPosY(r); 
		ball_vec[i]->setVelY(-vy);
	}

	if (y >= WINDOW_HEIGHT-r && vy > 0) {
		ball_vec[i]->setPosY(WINDOW_HEIGHT-r); 
		ball_vec[i]->setVelY(-vy);
	}
}

void CircleCollisionCheck(int i) {

	int numBalls = ball_vec.size();

	for (int j = i+1; j < numBalls; ++j) {

		// simple collision check between balls
		if (SquareCollisionCheck(*ball_vec[i], *ball_vec[j])) {

			// do a more complicated collision check
			if (CircleCollisionCheck(*ball_vec[i], *ball_vec[j])) {

				// if they still collide, resolve collision
				ResolveCollision(*ball_vec[i], *ball_vec[j]);
			}
		}
	}
}

void ResolveCollision(Ball &a, Ball &b) {	// SOMETHINGS WRONG; THEY ARE EXPLODING ON COLLISISON

	// Ball a
	float ax 	= a.getPosX();
	float ay 	= a.getPosY();
	float avx 	= a.getVelX();
	float avy 	= a.getVelY();
	float ar 	= a.getRadi();
	float am 	= a.getMass();

	// Ball b
	float bx 	= b.getPosX();
	float by 	= b.getPosY();
	float bvx 	= b.getVelX();
	float bvy 	= b.getVelY();
	float br 	= b.getRadi();
	float bm 	= b.getMass();

	float d1 = atan2(avy, avx);
	float d2 = atan2(bvy, bvx);
	float mag1 = sqrt(avx*avx+avy*avy);
	float mag2 = sqrt(bvx*bvx+bvy*bvy);
	float m1 = am;
	float m2 = bm;


	// distance from the center of each ball
	float dx = bx - ax;
	float dy = by - ay;
	float distance = sqrt(dx*dx+dy*dy);
	
	// collision depth
	float colDepth = (ar+br) - distance;
	
	// contact angle
	float colAngle = atan2(dy, dx);

	// dot product
	float vdx = bvx - avx;
	float vdy = bvy - avy;
 	float dotProduct = dx*vdx+dy*vdy;

 	// move the balls away from eachother so they dont overlap
 	float a_move_x = -colDepth*0.5*cos(colAngle);
 	float a_move_y = -colDepth*0.5*sin(colAngle);
 	float b_move_x = colDepth*0.5*cos(colAngle);
 	float b_move_y = colDepth*0.5*sin(colAngle);

 	if (ax + a_move_x >= ar && ax + a_move_x <= WINDOW_WIDTH - ar) {
 		a.addPosX(a_move_x);
 	}
 	if (ay + a_move_y >= ar && ay + a_move_y <= WINDOW_HEIGHT -  ar) {
 		a.addPosY(a_move_y);
 	}
 	if (bx + b_move_x >= br && bx + b_move_x <= WINDOW_WIDTH - br) {
 		b.addPosX(b_move_x);
 	}
 	if (by + b_move_y >= br && by + b_move_y <= WINDOW_HEIGHT - br) {
 		b.addPosY(b_move_y);
 	}

 	ax 	= a.getPosX();
	ay 	= a.getPosY();
	bx 	= b.getPosX();
	by 	= b.getPosY();

 	//calculate from the new position
 	dx = bx - ax;
	dy = by - ay;

	//distance = sqrt(dx*dx+dy*dy);
	colAngle = atan2(dy, dx);


 	// dont calc if they are moving away form eachother
 	if (dotProduct < 0){

 		#define PI 3.1415926

		float nv1x = mag1*cos(d1-colAngle);
		float nv1y = mag1*sin(d1-colAngle);
		float nv2x = mag2*cos(d2-colAngle);
		float nv2y = mag2*sin(d2-colAngle);

		float v1xf = ((m1-m2)*nv1x+(m2+m2)*nv2x) / (m1+m2);
		float v2xf = ((m1+m1)*nv1x+(m2-m1)*nv2x) / (m1+m2);
		float v1yf = nv1y;
		float v2yf = nv2y;

		a.addVelX((cos(colAngle)*v1xf+cos(colAngle+PI*0.5)*v1yf*0.9));
		a.addVelY((sin(colAngle)*v1xf+sin(colAngle+PI*0.5)*v1yf*0.9));
		b.addVelX((cos(colAngle)*v2xf+cos(colAngle+PI*0.5)*v2yf*0.9));
		b.addVelY((sin(colAngle)*v2xf+sin(colAngle+PI*0.5)*v2yf*0.9));
	}
} 

void CalculateGravity(Ball& a, const Ball& b) {

	// Ball a
	float ax 	= a.getPosX();
	float ay 	= a.getPosY();
	float am 	= a.getMass();
	float acr 	= a.getColR();
	float acg 	= a.getColG();
	float acb 	= a.getColB();

	// Ball b
	float bx 	= b.getPosX();
	float by 	= b.getPosY();
	float bm 	= b.getMass();
	float bcr 	= b.getColR();
	float bcg 	= b.getColG();
	float bcb 	= b.getColB();

	if (gravForceCol && 
		acr == bcr && 
		acg == bcg && 
		acb == bcb) {
		
		float x1 = ax;
		float x2 = bx;
		float y1 = ay;
		float y2 = by;

		// Mass of the balls.
		float m1 = am;
		float m2 = bm;

		// Get distance between balls.
		float dx = x2-x1;
		float dy = y2-y1;
		float d = sqrt(dx*dx+dy*dy);

		if (d != 0) {

			float angle = atan2(dy, dx);
		
			float G = 6.674e-2;
		
			float F = G*m1*m2/d*d;
		
			a.addVelX(F*cos(angle));
			a.addVelY(F*sin(angle));
		}

	} else if (!gravForceCol) {

		float x1 = ax;
		float x2 = bx;
		float y1 = ay;
		float y2 = by;

		// Mass of the balls.
		float m1 = am;
		float m2 = bm;

		// Get distance between balls.
		float dx = x2-x1;
		float dy = y2-y1;
		float d = sqrt(dx*dx+dy*dy);

		if (d != 0) {

			float angle = atan2(dy, dx);
		
			float G = 6.674e-2;
		
			float F = G*m1*m2/d*d;
		
			a.addVelX(F*cos(angle));
			a.addVelY(F*sin(angle));
		}
	}
}

bool CircleCollisionCheck(const Ball& a, const Ball& b) {

	// Ball a
	float ax = a.getPosX();
	float ay = a.getPosY();
	float ar = a.getRadi();

	// Ball b
	float bx = b.getPosX();
	float by = b.getPosY();
	float br = b.getRadi();

	float dx = bx - ax;
    float dy = by - ay;
    float sumRadius = ar + br;
    float sqrRadius = sumRadius * sumRadius;

    float distSqr = (dx * dx) + (dy * dy);

    if (distSqr <= sqrRadius) {
        return true;
    }

    return false;
}

bool SquareCollisionCheck(const Ball& a, const Ball& b) {

	// Ball a
	float ax = a.getPosX();
	float ay = a.getPosY();
	float ar = a.getRadi();

	// Ball b
	float bx = b.getPosX();
	float by = b.getPosY();
	float br = b.getRadi();

	// basic square collision check
	if (ax - ar < bx + br && 
		ax + ar > bx - br &&
		ay - ar < by + br &&
		ay + ar > by - br) {

		return true;

	}

	return false;
}