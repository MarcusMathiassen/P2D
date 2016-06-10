#include "Rect.h"

#include <OpenGL/gl.h>
#include "Config.h"
#include "Vec2.h"
#include "Utility.h"

Rect::Rect() : p1(Vec2(0,0)), p2(Vec2(0,0)) {}

Rect::Rect(const Vec2& a, const Vec2& b) : p1(a), p2(b)
{
	assignColor(m_color);
	uniCol++;
}

void Rect::draw() const {

	glColor3ub(m_color.r,m_color.g,m_color.b);
	glBegin(GL_LINE_LOOP);
		glVertex2i(p1.x,p1.y);
		glVertex2i(p1.x,p2.y);
		glVertex2i(p2.x,p2.y);
		glVertex2i(p2.x,p1.y);
	glEnd();
}

bool Rect::contains(const Circle& a) const
{
	Vec2 b = a.getPos();
	float ar = a.getRadi();

	if(b.x < p1.x || b.x > p2.x) return false;
    if(b.y < p1.y || b.y > p2.y) return false;

	return true;
}

Vec2 Rect::getP1() const { return p1; }
Vec2 Rect::getP2() const { return p2; }
Color Rect::getColor() const {return m_color; }