#include "Quadtree.h"

Quadtree quadtree(0,Rect(Vec2(0,0),Vec2(screen_width,screen_height)));

Quadtree::Quadtree(int level, const Rect& bounds) :
m_level(level),
m_bounds(bounds),
m_subnode{nullptr,nullptr,nullptr,nullptr}
{
	m_index.reserve(NODE_CAPACITY);
}


void Quadtree::update()
{
	//-----------------------------------------------------------------------------------
	// Clear the quadtree and insert it with objects.
	//-----------------------------------------------------------------------------------

	m_index.clear();
	m_index.shrink_to_fit();

	m_subnode[0] = nullptr;
	m_subnode[1] = nullptr;
	m_subnode[2] = nullptr;
	m_subnode[3] = nullptr;


	for (const auto& object: object_vec)
	{
		insert(*object);
	}
}


void Quadtree::get(vec<vec<int>>& cont) const
{
	//-----------------------------------------------------------------------------------
	// [1] Find the deepest level node.
	// [2] Add the indexes to the container.
	//-----------------------------------------------------------------------------------

	if (m_subnode[0] != nullptr)													// [1]
	{
		m_subnode[0]->get(cont);
		m_subnode[1]->get(cont);
		m_subnode[2]->get(cont);
		m_subnode[3]->get(cont);
	}

	if (m_index.size() > 0)															// [2]
	{
		cont.emplace_back(m_index);
	}
}


void Quadtree::split()
{
	//-----------------------------------------------------------------------------------
	// Creates subnodes and gives each its own quadrant.
	//-----------------------------------------------------------------------------------

	Vec2 min 	= m_bounds.get_min();
	Vec2 max 	= m_bounds.get_max();

	int x		= min.x;
	int y 		= min.y;
	int w 		= max.x-min.x;
	int h 		= max.y-min.y;

	int h_w 	= w * 0.5;
	int h_h 	= h * 0.5;

	Rect SW 	(Vec2(x,y), 		Vec2(x+h_w,y+h_h));
	Rect SE 	(Vec2(x+h_w,y), 	Vec2(x+w,y+h_h));
	Rect NW 	(Vec2(x,y+h_h), 	Vec2(x+h_w,y+h));
	Rect NE 	(Vec2(x+h_w,y+h_h), Vec2(x+w,y+h));

	m_subnode[0] = std::make_unique<Quadtree>(m_level+1,SW);
	m_subnode[1] = std::make_unique<Quadtree>(m_level+1,SE);
	m_subnode[2] = std::make_unique<Quadtree>(m_level+1,NW);
	m_subnode[3] = std::make_unique<Quadtree>(m_level+1,NE);
}


void Quadtree::insert(const Circle& object)
{
	//-----------------------------------------------------------------------------------
	// [1] Insert object into subnodes.
	// [2] If split, insert THIS nodes objects into the subnodes.
	// [3] Add object to this node.
	//-----------------------------------------------------------------------------------

	if (m_subnode[0] != nullptr)
	{
		bool inNodes = false;
		for (int i = 0; i < 4; ++i)
		{
			if (m_subnode[i]->contains(object)) 					// [1]
			{
				m_subnode[i]->insert(object);
				inNodes = true;
			}
		}
		if (inNodes) return;
	}

	if (m_index.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH)
	{
		if (m_subnode[0] == nullptr)
		{
			split();

			for (const auto& index: m_index) 						// [2]
			{
				for (const auto& subnode: m_subnode)
				{
					if (subnode->contains(*object_vec[index]))
					{
						subnode->insert(*object_vec[index]);
					}
				}
			}

			// Remove all indexes from THIS node
			m_index.clear();
			m_index.shrink_to_fit();
		}

		return;
	}

	m_index.emplace_back(object.get_index());						// [3]
}


void Quadtree::reset()
{
	//-----------------------------------------------------------------------------------
	// Sets bounds to the screens bounds and clears the quadtrees.
	//-----------------------------------------------------------------------------------

	m_bounds = Rect(Vec2(0,0),Vec2(screen_width,screen_height));

	m_index.clear();
	m_index.shrink_to_fit();

	m_subnode[0] = nullptr;
	m_subnode[1] = nullptr;
	m_subnode[2] = nullptr;
	m_subnode[3] = nullptr;
}


void Quadtree::draw() const
{
	//-----------------------------------------------------------------------------------
	// [1] Draw this nodes boundaries.
	// [2] Draw subnodes boundaries.
	//-----------------------------------------------------------------------------------

	m_bounds.draw();												// [1]

	if (m_subnode[0] != nullptr)									// [2]
	{
		m_subnode[0]->draw();
		m_subnode[1]->draw();
		m_subnode[2]->draw();
		m_subnode[3]->draw();
	}
}


bool Quadtree::contains(const Circle& object) const
{
	if (m_bounds.contains(object)) return true;
	return false;
}
