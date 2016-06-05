#ifndef _CIRCLE_H
#define _CIRCLE_H

#include "Vec2.h"
#include "Color.h"

class Circle : public Object {

private:
	
	Vec2		m_pos;
	Vec2		m_vel;
	float		m_radi;
	float		m_mass;
	color		m_color;
	int			m_vertices;

public:

	Circle(const Vec2& p, float r, int v);
	Circle(const Circle& c);

	void draw() const;
	void update();

	Vec2 	getPos() 		const;
	Vec2 	getVel() 		const;
	float 	getMass()	 	const;
	float 	getRadi() 		const;
	int 	getVertices() 	const;
	Color 	getCol() 		const;

};

#endif