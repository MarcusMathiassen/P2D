
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Circle.h"

Circle::Circle(const Vec2& p, float r, int v) : m_pos(p), m_radi(r), m_vertices(v) {
	m_vel = Vec2(0,0);
	m_mass = m_radi;
	assignColor(m_color);
	m_tempcolor = white;

	m_index = object_vec.size();		// Object index is it´s number in the vector.

	m_cosineTable.reserve(m_vertices+1);
	m_sineTable.reserve(m_vertices+1);
	m_cosineTable[0] = m_radi;
	m_sineTable[0] = 0; 	
	for (int i = 1; i <= m_vertices; ++i) {
		m_cosineTable[i] 	= (m_radi * cos(i *  DOUBLE_PI / m_vertices));
		m_sineTable[i] 		= (m_radi * sin(i *  DOUBLE_PI / m_vertices));
	}
}

void Circle::draw()
{
	// Draw the circle.
	if (show_DynamicGrid && use_DynamicGrid) glColor3ub(m_tempcolor.r,m_tempcolor.g,m_tempcolor.b);
	else glColor3ub(m_color.r,m_color.g,m_color.b);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(m_pos.x, m_pos.y);
	for(int i = 0; i <= m_vertices; ++i) { 
		glVertex2f(m_pos.x+m_cosineTable[i], m_pos.y+m_sineTable[i]);
	}
	glEnd();
}

void Circle::debug() const
{
	// Draws lines showing the direction
	float angle 	= atan2(m_vel.y,m_vel.x);	
	float ny 		= m_pos.y + m_radi*2 * sin(angle);
	float nx 		= m_pos.x + m_radi*2 * cos(angle);
	
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH); 
	if (show_DynamicGrid && use_DynamicGrid) glColor3ub(m_tempcolor.r,m_tempcolor.g,m_tempcolor.b);
	else glColor3ub(m_color.r,m_color.g,m_color.b);
	glBegin(GL_LINES);
		glVertex2d(m_pos.x,m_pos.y);
		glVertex2d(nx,ny);
	glEnd();
	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH); 
}

void Circle::update()
{
	// Border collision check
	if (borderCol) {
		if (m_pos.x <= m_radi && m_vel.x < 0) {		
			m_pos.x = (m_radi); 
			m_vel.x = (-m_vel.x);	
		}
	
		if (m_pos.x >= screen_width-m_radi && m_vel.x > 0) { 
			m_pos.x = (screen_width-m_radi); 
			m_vel.x = (-m_vel.x);
		}
	
		if (m_pos.y <= m_radi && m_vel.y < 0) {
			m_pos.y = (m_radi); 
			m_vel.y = (-m_vel.y);
		}
	
		if (m_pos.y >= screen_height-m_radi && m_vel.y > 0) {
			m_pos.y = (screen_height-m_radi); 
			m_vel.y = (-m_vel.y);
		}
	}

	float slow = 1;
	if(slowmotion) slow = 0.1;
	
	m_mass = m_radi*0.1;
	if(gravity) m_vel.y -= ACCEL * m_mass*slow;
	
	if (gravForce) {
	    for (size_t i = 0; i < object_vec.size(); ++i) {
	        gravitationForce(static_cast<Circle&>(*object_vec[i]));
	    }
	}

	// Update ball position
	m_pos.x += (m_vel.x * 60*(0.0001*slow));
	m_pos.y += (m_vel.y * 60*(0.0001*slow));
}

bool Circle::collisionDetection(const Circle& b) const
{	
	if (show_FPS) comparisons++;

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

void Circle::changeColor(const Color& c)
{
	m_tempcolor = c;
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
	float cosOfAngle = cos(colAngle);
	float sinOfAngle = sin(colAngle);

	// dot product
	float vdx = bvx - m_vel.x;
	float vdy = bvy - m_vel.y;
 	float dotProduct = dx*vdx+dy*vdy;

 	// move the balls away from eachother so they dont overlap
 	float a_move_x = -colDepth*0.5*cosOfAngle;
 	float a_move_y = -colDepth*0.5*sinOfAngle;
 	float b_move_x = colDepth*0.5*cosOfAngle;
 	float b_move_y = colDepth*0.5*sinOfAngle;

 	if (m_pos.x + a_move_x >= m_radi && m_pos.x + a_move_x <= screen_width - m_radi) {
 		m_pos.x += (a_move_x);
 	}
 	if (m_pos.y + a_move_y >= m_radi && m_pos.y + a_move_y <= screen_height -  m_radi) {
 		m_pos.y += (a_move_y);
 	}
 	if (bx + b_move_x >= br && bx + b_move_x <= screen_width - br) {
 		b.addPosX(b_move_x);
 	}
 	if (by + b_move_y >= br && by + b_move_y <= screen_height - br) {
 		b.addPosY(b_move_y);
 	}

 	// dont calc if they are moving away form eachother
 	if (dotProduct < 0){

		float nv1x = mag1*cos(d1-colAngle);
		float nv1y = mag1*sin(d1-colAngle);
		float nv2x = mag2*cos(d2-colAngle);
		float nv2y = mag2*sin(d2-colAngle);

		float v1xf = ((m1-m2)*nv1x+(m2+m2)*nv2x) / (m1+m2);
		float v2xf = ((m1+m1)*nv1x+(m2-m1)*nv2x) / (m1+m2);
		float v1yf = nv1y;
		float v2yf = nv2y;

		float cos_angle_halfpi = cos(colAngle+HALF_PI);
		float sin_angle_halfpi = sin(colAngle+HALF_PI);

		m_vel.x = (cosOfAngle*v1xf+cos_angle_halfpi*v1yf);
		m_vel.y = (sinOfAngle*v1xf+sin_angle_halfpi*v1yf);

		b.setVel(
			(cosOfAngle*v2xf+cos_angle_halfpi*v2yf),
			(sinOfAngle*v2xf+sin_angle_halfpi*v2yf));
	}
}

void Circle::gravitationForce(const Circle& b)
{
    // Set up variables
    Vec2 bpos = b.getPos();
    float x1 = m_pos.x;
    float x2 = bpos.x;
    float y1 = m_pos.y;
    float y2 = bpos.y;
    
    // Mass of the balls.
    float m1 = m_mass;
    float m2 = b.getMass();
    
    // Get distance between balls.
    float dx = x2-x1;
    float dy = y2-y1;
    float d = sqrt(dx*dx+dy*dy);
    
    if (d != 0) {
    	
        float angle = atan2(dy, dx);
        const float G = 6.674e-2;
        float F = G*m1*m2/d*d;
        
        m_vel.x += F*cos(angle);
        m_vel.y += F*sin(angle);
        
    }
}

int 	Circle::getIndex() const 			{return m_index;}
Vec2 	Circle::getPos() const 				{return m_pos;}
void 	Circle::addPosX(float f)			{m_pos.x += f;}
void 	Circle::addPosY(float f)			{m_pos.y += f;}
Vec2 	Circle::getVel() const				{return m_vel;}
void	Circle::setVel(float x, float y)	{m_vel.x = x,m_vel.y = y;}
void 	Circle::addVel(float x, float y)	{m_vel.x += x,m_vel.y += y;}
void 	Circle::addVelX(float f)			{m_vel.x += f;}
void 	Circle::addVelY(float f)			{m_vel.y += f;}
float 	Circle::getMass() const 			{return m_mass;}
float 	Circle::getRadi() const				{return m_radi;}
int 	Circle::getVertices() const			{return m_vertices;}
Color 	Circle::getColor() const			{return m_color;}
Color 	Circle::getTempColor() const		{return m_tempcolor;}
