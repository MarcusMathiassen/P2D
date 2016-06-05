#include "Circle.h"

#include <cmath>			// cos, sin
#include <GL/glew.h>		// gl functions

#include "Vec2.h"
#include "Color.h"

Circle::Circle(const Vec2& p, float r, int v) : m_pos(p), m_radi(r), m_vertices(v) {}
Circle::Circle(const Circle& c)
{
	m_pos 		= c.getPos();
	m_vel		= c.getVel();
	m_mass		= c.getMass();
	m_radi 		= c.getRadi();
	m_color 	= c.getColor();
	m_vertices 	= c.getVertices();
}

void Circle::draw() const 
{
	const float doublePI = 6.283185;
	glColor3ub(m_color.r,m_color.g,m_color.b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(m_pos.x, m_pos.y);
	for(int i = 0; i <= m_vertices; ++i) { 
		glVertex2f(
	        m_pos.x + (m_radi * cos(i *  doublePI / m_vertices)), 
		    m_pos.y + (m_radi * sin(i *  doublePI / m_vertices))
		);
	}
	glEnd();
}

void Circle::update()
{

}

Vec2 	Circle::getPos() 		const 	{ return m_pos;			}
Vec2 	Circle::getVel() 		const	{ return m_vel;			}
float 	Circle::getMass()	 	const 	{ return m_mass;		}
float 	Circle::getRadi() 		const	{ return m_radi;		}
int 	Circle::getVertices() 	const	{ return m_vertices; 	}
Color 	Circle::getCol() 		const	{ return m_color; 		}