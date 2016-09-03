
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Rect.h"

Rect::Rect() : min(Vec2(0,0)), max(Vec2(0,0)) {}

Rect::Rect(const Vec2& a, const Vec2& b) : min(a), max(b)
{
	assignColor(m_color);
	if (use_fixedgrid) uniCol++;
}

void Rect::draw() const
{
	glColor3ub(m_color.r,m_color.g,m_color.b);
	glLineWidth(1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(min.x+1,min.y+1);
		glVertex2f(min.x+1,max.y-1);
		glVertex2f(max.x-1,max.y-1);
		glVertex2f(max.x-1,min.y+1);
	glEnd();
}

bool Rect::contain(const Circle& a) const
{
	Vec2 b = a.get_pos();
	float ar = a.get_radi();

	//  basic square collision check
	if (b.x - ar < max.x &&
		b.x + ar > min.x &&
		b.y - ar < max.y &&
		b.y + ar > min.y)
	{
		return true;
	}

	return false;
}

bool Rect::containsPos(const Circle &a) const
{
	Vec2 b = a.get_pos();
	if(b.x < min.x || b.x > max.x) return false;
	if(b.y < min.y || b.y > max.y) return false;

	return true;
}

Vec2 Rect::get_min() const 			{return min;}
Vec2 Rect::get_max() const 			{return max;}
Color Rect::get_color() const 		{return m_color;}
void Rect::set_color(const Color& c) {m_color = c;}