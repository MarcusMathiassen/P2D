#ifndef FIXEDGRID_H
#define FIXEDGRID_H

#include <memory>
#include <cmath>
#include "Object.h"
#include "Rect.h"
#include "Config.h"

namespace FixedGrid
{

// A node for each element in our grid
struct Node
{	
	Rect 										m_rect;
	std::vector<std::unique_ptr<Object>> 		m_object_vec;

	Node(const Rect& r) : m_rect(r) {}
};

// Split 

void init();

	std::vector<Node> node_vec;

	int sqrtGrid = sqrt(uniGrids);
	int col = screen_width / sqrtGrid;  // 500 / 2; 250;
	int row = screen_height / sqrtGrid; // 500 / 2; 250;


	node_vec.reserve(uniGrids);

	// Assign grid positions
	for (int i = 0; i < uniGrids; ++i)
	{
		node_vec[i].m_rect = Vec(col*i,row*i),Vec(maxx*i,maxy*i);
	}

};

#endif