
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include <cmath>								// cos, sin, sqrt, atan2
#include <OpenGL/gl.h>							// for drawing to screen

#include "../Object.h"
#include "../../Utility/Templates.h"			// vec
#include "../../Utility/Vec2.h"					// Vec2 class
#include "../../Utility/Color.h"				// Color class
#include "../../Utility/Utility.h"				// assignColor()
#include "../../Config.h"						// Global vars, screen size

#define PI 3.14159
#define HALF_PI 1.570796
#define DOUBLE_PI 6.283185

class Circle : public Object
{

private:

	Vec2					m_pos;
	Vec2					m_vel;
	float					m_radi;
	float					m_mass;
	Color					m_color;
	Color 					m_tempcolor;
	int						m_vertices;

	vec<float> 				m_cosineTable;
	vec<float> 	 			m_sineTable;

public:

	Circle(const Vec2& p, float r, int v);

	void draw();
	void update();
	void debug() const;
	void changeColor(const Color& c);

    void gravitationForce(const Circle& b);

	bool collisionDetection(const Circle& b) const;
	void resolveCollision(Circle& b);

	// ------- GET/SET ---------
	int 	getIndex() const;
	Vec2 	getPos() const;
	Vec2 	getVel() const;
	void 	addPosX(float f);
	void 	addPosY(float f);
	void	setVel(float x, float y);
	void 	addVel(float x, float y);
	void	addVelX(float f);
	void 	addVelY(float f);
	float 	getMass() const;
	float 	getRadi() const;
	int 	getVertices() const;
	Color 	getColor() const;
	Color 	getTempColor() const;
};

#endif