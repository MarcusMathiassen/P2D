#ifndef _CIRCLE_H
#define _CIRCLE_H

#include <vector>
#include "Object.h"
#include "Vec2.h"
#include "Color.h"

class Circle : public Object {

private:
	
	Vec2					m_pos;
	Vec2					m_vel;
	float					m_radi;
	float					m_mass;
	Color					m_color;
	Color 					m_tempcolor;
	int						m_vertices;

	std::vector<float> 		m_cosineTable;
	std::vector<float> 	 	m_sineTable;
	bool					m_isOnScreen;

public:

	Circle(const Vec2& p, float r, int v);
	Circle(const Circle& c);

	void draw() const;
	void update();
	void debug() const;
	void changeColor(const Color& c);
    
    void gravitationForce(const Circle& b);
	
	bool collisionDetection(const Circle& b) const;
	void resolveCollision(Circle& b);

	Vec2 	getPos() 					const;
	Vec2 	getVel()					const;
	void 	addPosX(float f);	
	void 	addPosY(float f);	
	void	setVel(float x, float y);
	void 	addVel(float x, float y);
	void	addVelX(float f);
	void 	addVelY(float f);
	float 	getMass()	 				const;
	float 	getRadi() 					const;
	int 	getVertices() 				const;
	Color 	getColor() 					const;
	Color 	getTempColor()				const;

};

#endif