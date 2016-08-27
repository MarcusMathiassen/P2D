
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include <cmath>								// cos, sin, sqrt, atan2
#include <OpenGL/gl.h>							// for drawing to screen

#include "../../Utility/Templates.h"			// vec
#include "../../Utility/Vec2.h"					// Vec2 class
#include "../../Utility/Color.h"				// Color class
#include "../../Utility/Utility.h"				// assignColor()
#include "../../Config/Config.h"				// Global vars, screen size

class Circle
{

private:

	Vec2					m_pos;
	Vec2					m_vel;
	float					m_radi;
	float					m_mass;
	Color					m_color;
	Color 					m_temp_color;
	int						m_vertices;

	vec<float> 				m_cosineTable;
	vec<float> 	 			m_sineTable;

	int 					m_index;

public:

	Circle(const Vec2& p, float r, int v);

	void draw() const;
	void update();
	void debug() const;

    void gravitationforce(const Circle& b);

	bool collision_detection(const Circle& b) const;
	void collision_resolve(Circle& b);

	// ------- GET/SET ---------
	int 	get_index() const;
	Vec2 	get_pos() const;
	Vec2 	get_vel() const;
	void 	add_pos_x(float f);
	void 	add_pos_y(float f);
	void	set_vel(float x, float y);
	void	set_vel(const Vec2& v);
	void 	add_vel(float x, float y);
	void	add_vel_x(float f);
	void 	add_vel_y(float f);
	float 	get_mass() const;
	float 	get_radi() const;
	int 	get_vertices() const;
	Color 	get_color() const;
	void	set_temp_color(const Color& c);
};

extern vec<uptr<Circle> > object_vec;

#endif