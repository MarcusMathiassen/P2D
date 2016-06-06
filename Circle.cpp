#include "Circle.h"

#include <cmath>			// cos, sin
#include <GL/glew.h>		// gl functions

#include "Config.h"			// Global variables
#include "Utility.h"		// assignColor()
#include "Vec2.h"
#include "Color.h"

Circle::Circle(const Vec2& p, float r, int v) : m_pos(p), m_radi(r), m_vertices(v) {
	m_vel = Vec2(0,0);
	m_mass = m_radi;
	assignColor(m_color);
}

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
	// Draw the circle.
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

void Circle::debug() const
{
	// Draws lines showing the direction and velocity.
	if (direction) {
		float distance 	= sqrt(m_vel.x*m_vel.x+m_vel.y*m_vel.y);
		float angle 	= atan2(m_vel.y,m_vel.x);	
		float ny 		= m_pos.y + distance * sin(angle);
		float nx 		= m_pos.x + distance * cos(angle);
		glColor3ub(m_color.r,m_color.g,m_color.b);
		glBegin(GL_LINES);
			glVertex2d(m_pos.x,m_pos.y);
			glVertex2d(m_vel.x+nx,m_vel.y+ny);
		glEnd();
	}
}

void Circle::update()
{
	m_mass = m_radi;
	if(gravity) m_vel.y -= ACCEL * m_mass;

	int slow = 0;
	if(slowmotion) slow = 10;
	else slow = 1;

	// Update ball position
	m_pos.x += (m_vel.x * 16.667/(1000*slow));
	m_pos.y += (m_vel.y * 16.667/(1000*slow));

	// Border collision check
	if (borderCol) {
		if (m_pos.x <= m_radi && m_vel.x < 0) {		
			m_pos.x = (m_radi); 
			m_vel.x = (-m_vel.x)*0.9;		
		}
	
		if (m_pos.x >= WINDOW_WIDTH-m_radi && m_vel.x > 0) { 
			m_pos.x = (WINDOW_WIDTH-m_radi); 
			m_vel.x = (-m_vel.x)*0.9;
		}
	
		if (m_pos.y <= m_radi && m_vel.y < 0) {
			m_pos.y = (m_radi); 
			m_vel.y = (-m_vel.y)*0.9;
		}
	
		if (m_pos.y >= WINDOW_HEIGHT-m_radi && m_vel.y > 0) {
			m_pos.y = (WINDOW_HEIGHT-m_radi); 
			m_vel.y = (-m_vel.y)*0.9;
		}
	}
}

bool Circle::collisionDetection(const Circle& b) const
{	
	// Setup variables
	Vec2 bpos = b.getPos();
	float bx = bpos.x;
	float by = bpos.y;
	float br = b.getRadi();

	//  basic square collision check
	if (m_pos.x - m_radi < bx + br && 
		m_pos.x + m_radi > bx - br &&
		m_pos.y - m_radi < by + br &&
		m_pos.y + m_radi > by - br) {

		// Circle collision check
		float dx = bx - m_pos.x;
    	float dy = by - m_pos.y;
    	float sumRadius = m_radi + br;
    	float sqrRadius = sumRadius * sumRadius;
	
    	float distSqr = (dx * dx) + (dy * dy);
	
    	if (distSqr <= sqrRadius) {
    	    return true;
    	} 
    }

    return false;
}

void Circle::resolveCollision(Circle& b)
{	
	// Setup variables
	Vec2 bpos = b.getPos();
	Vec2 bvel = b.getVel();
	float bx = bpos.x;
	float by = bpos.y;
	float bvx = bvel.x;
	float bvy = bvel.y;
	float br = b.getRadi();

	float d1 = atan2(m_vel.y, m_vel.x);
	float d2 = atan2(bvy, bvx);
	float mag1 = sqrt(m_vel.x*m_vel.x+m_vel.y*m_vel.y);
	float mag2 = sqrt(bvx*bvx+bvy*bvy);
	float m1 = m_mass;
	float m2 = b.getMass();


	// distance from the center of each ball
	float dx = bx - m_pos.x;
	float dy = by - m_pos.y;
	float distance = sqrt(dx*dx+dy*dy);
	
	// collision depth
	float colDepth = (m_radi+br) - distance;
	
	// contact angle
	float colAngle = atan2(dy, dx);

	// dot product
	float vdx = bvx - m_vel.x;
	float vdy = bvy - m_vel.y;
 	float dotProduct = dx*vdx+dy*vdy;

 	// move the balls away from eachother so they dont overlap
 	float a_move_x = -colDepth*0.5*cos(colAngle);
 	float a_move_y = -colDepth*0.5*sin(colAngle);
 	float b_move_x = colDepth*0.5*cos(colAngle);
 	float b_move_y = colDepth*0.5*sin(colAngle);

 	if (m_pos.x + a_move_x >= m_radi && m_pos.x + a_move_x <= WINDOW_WIDTH - m_radi) {
 		m_pos.x += (a_move_x);
 	}
 	if (m_pos.y + a_move_y >= m_radi && m_pos.y + a_move_y <= WINDOW_HEIGHT -  m_radi) {
 		m_pos.y += (a_move_y);
 	}
 	if (bx + b_move_x >= br && bx + b_move_x <= WINDOW_WIDTH - br) {
 		b.addPosX(b_move_x);
 	}
 	if (by + b_move_y >= br && by + b_move_y <= WINDOW_HEIGHT - br) {
 		b.addPosY(b_move_y);
 	}

 	//calculate from the new position
 	dx = bx - m_pos.x;
	dy = by - m_pos.y;
	//distance = sqrt(dx*dx+dy*dy);
	colAngle = atan2(dy, dx);

 	// dont calc if they are moving away form eachother
 	if (dotProduct < 0){

 		#define PI 3.14159265359
		float nv1x = mag1*cos(d1-colAngle);
		float nv1y = mag1*sin(d1-colAngle);
		float nv2x = mag2*cos(d2-colAngle);
		float nv2y = mag2*sin(d2-colAngle);

		float v1xf = ((m1-m2)*nv1x+(m2+m2)*nv2x) / (m1+m2);
		float v2xf = ((m1+m1)*nv1x+(m2-m1)*nv2x) / (m1+m2);
		float v1yf = nv1y;
		float v2yf = nv2y;

		m_vel.x = (cos(colAngle)*v1xf+cos(colAngle+PI/2)*v1yf*0.9);
		m_vel.y = (sin(colAngle)*v1xf+sin(colAngle+PI/2)*v1yf*0.9);

		b.setVel(
			(cos(colAngle)*v2xf+cos(colAngle+PI/2)*v2yf*0.9),
			(sin(colAngle)*v2xf+sin(colAngle+PI/2)*v2yf*0.9));
	}
}

Vec2 	Circle::getPos() 		const 	{ return m_pos;			}
void 	Circle::addPosX(float f)		{ m_pos.x += f;}
void 	Circle::addPosY(float f)		{ m_pos.y += f;}
Vec2 	Circle::getVel() 		const	{ return m_vel;			}
void	Circle::setVel(float x, float y){ m_vel.x = x,m_vel.y = y;}
void 	Circle::addVelX(float f)		{ m_vel.x += f;}
void 	Circle::addVelY(float f)		{ m_vel.y += f;}
float 	Circle::getMass()	 	const 	{ return m_mass;		}
float 	Circle::getRadi() 		const	{ return m_radi;		}
int 	Circle::getVertices() 	const	{ return m_vertices; 	}
Color 	Circle::getColor() 		const	{ return m_color; 		}