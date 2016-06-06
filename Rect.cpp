#include "Rect.h"

#include <GL/glew.h>	
#include "Config.h"
#include "Vec2.h"

Rect::Rect() : p1(Vec2(0,0)), p2(Vec2(0,0)) 
{
	//p1.x = (p1.x < p2.x) ? p1.x : p2.x;
	//p1.y = (p1.y < p2.y) ? p1.y : p2.y;
	//p2.x = (p1.x > p2.x) ? p1.x : p2.x;
	//p2.y = (p1.y > p2.y) ? p1.y : p2.y;
}

Rect::Rect(const Vec2& a, const Vec2& b) : p1(a), p2(b) {}

void Rect::draw() const {

	glColor3ub(0,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2i(p1.x,p1.y);
		glVertex2i(p1.x,p2.y);
		glVertex2i(p2.x,p2.y);
		glVertex2i(p2.x,p1.y);
	glEnd();

	glColor3ub(255,0,0);
	glBegin(GL_LINES);
		glVertex2i(p1.x,p1.y);
		glVertex2i(p2.x,p2.y);
	glEnd();

	glColor3ub(0,255,0);
	glBegin(GL_LINES);
		glVertex2i(p1.x,p2.y);
		glVertex2i(p2.x,p1.y);
	glEnd();
}

bool Rect::contains(const Vec2& a) const
{	
	int minx = (p1.x < p2.x) ? p1.x : p2.x;
	int miny = (p1.y < p2.y) ? p1.y : p2.y;
	int maxx = (p1.x > p2.x) ? p1.x : p2.x;
	int maxy = (p1.y > p2.y) ? p1.y : p2.y;

	if(a.x < minx || a.x > maxx) return false;
    if(a.y < miny || a.y > maxy) return false;
	return true;
}

Vec2 Rect::getP1() const { return p1; }
Vec2 Rect::getP2() const { return p2; }