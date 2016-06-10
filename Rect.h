#ifndef RECT_H
#define RECT_H

#include "Vec2.h"
#include "Color.h"
#include "Circle.h"

class Rect {

private:

	Vec2		p1,p2;
	Color		m_color;

public:

	Rect();
	Rect(const Vec2& a, const Vec2& b);

	void draw() const;

	bool contains(const Circle& a) const;

	Vec2 getP1() const;
	Vec2 getP2() const;
	Color getColor() const;
};

#endif