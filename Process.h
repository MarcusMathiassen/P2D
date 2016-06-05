#ifndef PROCESS_H
#define PROCESS_H

#include "Ball.h"

void update();

void CalcBall(int begin, int end);

void borderCollision(int i);

void CircleCollisionCheck(int i);
void ResolveCollision(Ball& a, Ball& b);
bool SquareCollisionCheck(const Ball& a, const Ball& b);
bool CircleCollisionCheck(const Ball& a, const Ball& b);

void CalculateGravity(Ball& a, const Ball& b);

#endif