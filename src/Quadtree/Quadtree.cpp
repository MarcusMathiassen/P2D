
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Quadtree.h"

Quadtree quadtree;

Quadtree::Quadtree() : m_level(0), m_bounds(Rect(Vec2(0,0),Vec2(screen_width,screen_height))),
m_subnode{nullptr,nullptr,nullptr,nullptr} {}

Quadtree::Quadtree(int level, const Rect& bounds) : m_level(level), m_bounds(bounds),
m_subnode{nullptr,nullptr,nullptr,nullptr} {}

void Quadtree::update()
{
	//---------------------------------------------------------------------
	// Clear the quadtree and insert it with objects.
	//---------------------------------------------------------------------

	m_index.clear();
	m_index.shrink_to_fit();

	m_subnode[0] = nullptr;
	m_subnode[1] = nullptr;
	m_subnode[2] = nullptr;
	m_subnode[3] = nullptr;

	// Insert objects into the quadtree
	for (const auto& object: object_vec)
	{
		insert(*object);
	}
}

void Quadtree::process() const
{
	//---------------------------------------------------------------------
	// [1] Find the deepest level node.
	// [2] Run collision/resolve on the nodes objects.
	//---------------------------------------------------------------------

	if (m_subnode[0] != nullptr)									//	[1]
	{
		m_subnode[0]->process();
		m_subnode[1]->process();
		m_subnode[2]->process();
		m_subnode[3]->process();

		return;
	}


	if (m_index.size() > 0)											//	[2]
	{
		for (size_t i = 0; i < m_index.size(); ++i)
		{
			for (size_t j = i+1; j < m_index.size(); ++j)
			{
				if (object_vec[m_index[i]]->collision_detection(*object_vec[m_index[j]]))
				{
					object_vec[m_index[i]]->collision_resolve(*object_vec[m_index[j]]);
				}
			}
		}
	}
}

void Quadtree::split()
{
	//---------------------------------------------------------------------
	// Creates subnodes and gives each its own quadrant.
	//---------------------------------------------------------------------

	Vec2 min 	= m_bounds.get_min();
	Vec2 max 	= m_bounds.get_max();

	int x		= min.x;
	int y 		= min.y;
	int width	= max.x-min.x;
	int height	= max.y-min.y;

	int subWidth 	= width * 0.5;
	int subHeight 	= height * 0.5;

	// SW
	m_subnode[0] = std::make_unique<Quadtree>(m_level+1,Rect(Vec2(x,y),Vec2(x+subWidth,y+subHeight)));
	// SE
	m_subnode[1] = std::make_unique<Quadtree>(m_level+1,Rect(Vec2(x+subWidth,y),Vec2(x+width,y+subHeight)));
	// NW
	m_subnode[2] = std::make_unique<Quadtree>(m_level+1,Rect(Vec2(x,y+subHeight),Vec2(x+subWidth,y+height)));
	// NE
	m_subnode[3] = std::make_unique<Quadtree>(m_level+1,Rect(Vec2(x+subWidth,y+subHeight),Vec2(x+width,y+height)));
}

void Quadtree::insert(const Circle& object)
{
	//---------------------------------------------------------------------
	// [1] Insert object into subnodes.
	// [2] If split, insert THIS nodes objects into the subnodes.
	// [3] Add object to this node.
	//---------------------------------------------------------------------

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

void Quadtree::clear()
{
	//---------------------------------------------------------------------
	// Sets bounds to the screens bounds and clears the quadtrees.
	//---------------------------------------------------------------------

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
	//---------------------------------------------------------------------
	// [1] Draw this nodes boundaries.
	// [2] Draw subnodes boundaries.
	//---------------------------------------------------------------------

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