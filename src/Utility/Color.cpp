#include "Color.h"

Color::Color() : r(0), g(0), b(0) {}
Color::Color(float i, float j, float k) : r(i), g(j), b(k) {}

Color Color::operator *(float f)
{
	return Color(r*f, g*f, b*f);
}

Color Color::operator +(const Color& c) const
{
	return Color((r+c.r)*0.5, (g+c.g)*0.5, (b+c.b)*0.5);
}

void Color::clamp()
{
		r = (r < 0) ? 0 : (r > 255) ? 255 : r;
		g = (g < 0) ? 0 : (g > 255) ? 255 : g;
		b = (b < 0) ? 0 : (b > 255) ? 255 : b;
}

// COLOR PRESETS
Color pastel_red		(255,105,97);
Color pastel_gray		(85,85,85);
Color pastel_green		(119,190,119);
Color pastel_orange		(255,179,71);
Color pastel_yellow		(253,253,150);
Color pastel_purple		(100,20,100);
Color pastel_blue		(119,158,203);
Color pastel_pink		(255, 209, 220);
Color black 			(0,0,0);
Color white				(255,255,255);
Color red 				(255,0,0);
Color green 			(0,255,0);
Color blue 				(0,0,255);
Color BCKGRND			(0.15,0.15,0.15);

int uniCol = 0;		// Our magic color wheel number