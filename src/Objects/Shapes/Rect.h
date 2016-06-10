#ifndef RECT_H
#define RECT_H

#include <OpenGL/gl.h>

#include "Circle.h"								// Circle class	
#include "../../Utility/Vec2.h"					// Vec2 class
#include "../../Utility/Color.h"				// Color class
#include "../../Utility/Utility.h"				// assignColor()
#include "../../Config.h"						// Global vars, screen size

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
	void setColor(const Color& c);
};

#endif