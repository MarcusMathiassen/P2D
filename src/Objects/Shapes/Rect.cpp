
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Rect.h"

Rect::Rect() : p1(Vec2(0,0)), p2(Vec2(0,0)) {}

Rect::Rect(const Vec2& a, const Vec2& b) : p1(a), p2(b)
{
	assignColor(m_color);
	if (use_DynamicGrid){
		uniCol++;
	}
}

void Rect::draw() const
{
	glColor3ub(m_color.r,m_color.g,m_color.b);
	glBegin(GL_LINE_LOOP);
		glVertex2f(p1.x+1,p1.y+1);
		glVertex2f(p1.x+1,p2.y-1);
		glVertex2f(p2.x-1,p2.y-1);
		glVertex2f(p2.x-1,p1.y+1);
	glEnd();
}

bool Rect::contains(const Circle& a) const
{
	Vec2 b = a.getPos();
	float ar = a.getRadi();

	//  basic square collision check
	if (b.x - ar < p2.x &&
		b.x + ar > p1.x &&
		b.y - ar < p2.y &&
		b.y + ar > p1.y)
	{
		return true;
	}

	return false;
}

bool Rect::containsPos(const Circle &a) const
{
	Vec2 b = a.getPos();
	if(b.x < p1.x || b.x > p2.x) return false;
	if(b.y < p1.y || b.y > p2.y) return false;

	return true;
}

Vec2 Rect::getP1() const 			{return p1;}
Vec2 Rect::getP2() const 			{return p2;}
Color Rect::getColor() const 		{return m_color;}
void Rect::setColor(const Color& c) {m_color = c;}