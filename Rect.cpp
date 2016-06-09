#include "Rect.h"

#include <OpenGL/gl.h>
#include "Config.h"
#include "Vec2.h"

Rect::Rect() : p1(Vec2(0,0)), p2(Vec2(0,0)) {}

Rect::Rect(const Vec2& a, const Vec2& b) : p1(a), p2(b) {}

void Rect::draw() const {

	glColor3ub(255,255,255);
	glBegin(GL_LINE_LOOP);
		glVertex2i(p1.x,p1.y);
		glVertex2i(p1.x,p2.y);
		glVertex2i(p2.x,p2.y);
		glVertex2i(p2.x,p1.y);
	glEnd();
}

bool Rect::contains(const Vec2& a) const
{
	if(a.x < p1.x || a.x > p2.x) return false;
    if(a.y < p1.y || a.y > p2.y) return false;
	return true;
}

Vec2 Rect::getP1() const { return p1; }
Vec2 Rect::getP2() const { return p2; }