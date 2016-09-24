
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef RECT_H
#define RECT_H

#include <OpenGL/gl.h>

#include "../Circle/Circle.h"					// Circle class
#include "../../Utility/Vec2.h"					// Vec2 class
#include "../../Utility/Color.h"				// Color class
#include "../../Utility/Utility.h"				// assignColor()
#include "../../Config/Config.h"				// Global vars, screen size

class Rect
{

private:

	Vec2		min,max;
	Color		m_color;

public:

	Rect();
	Rect(const Vec2& a, const Vec2& b);

	void draw() const;

	bool contain(const Circle& a) const;
	bool contain(const Rect &r) const;
	bool containsPos(const Circle& a) const;

	Vec2 get_min() const;
	Vec2 get_max() const;
	Color get_color() const;
	void set_color(const Color& c);
};

#endif