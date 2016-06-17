
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

Quadtree::~Quadtree()
{
	delete m_subnode[0];
	delete m_subnode[1];
	delete m_subnode[2];
	delete m_subnode[3];
}
void Quadtree::reset()
{
	m_index.clear();
	m_index.shrink_to_fit();
	delete m_subnode[0];
	delete m_subnode[1];
	delete m_subnode[2];
	delete m_subnode[3];
	m_subnode[0] = nullptr;
	m_subnode[1] = nullptr;
	m_subnode[2] = nullptr;
	m_subnode[3] = nullptr;
	m_bounds = Rect(Vec2(0,0),Vec2(screen_width,screen_height));
}

void Quadtree::split()
{
	Vec2 p1 	= m_bounds.getP1();
	Vec2 p2 	= m_bounds.getP2();

	int x		= p1.x;
	int y 		= p1.y;
	int width	= p2.x-p1.x;
	int height	= p2.y-p1.y;

	int subWidth 	= width * 0.5;
	int subHeight 	= height * 0.5;

	m_subnode[0] = new Quadtree(m_level+1,Rect(Vec2(x,y),Vec2(x+subWidth,y+subHeight)));
	m_subnode[1] = new Quadtree(m_level+1,Rect(Vec2(x+subWidth,y),Vec2(x+width,y+subHeight)));
	m_subnode[2] = new Quadtree(m_level+1,Rect(Vec2(x,y+subHeight),Vec2(x+subWidth,y+height)));
	m_subnode[3] = new Quadtree(m_level+1,Rect(Vec2(x+subWidth,y+subHeight),Vec2(x+width,y+height)));

	m_subnode[0]->setColor(pastel_red);
	m_subnode[1]->setColor(pastel_gray);
	m_subnode[2]->setColor(pastel_orange);
	m_subnode[3]->setColor(pastel_pink);
}

void Quadtree::insert(const Circle& b)
{
	//---------------------------------------------------------------------
	// Go as far down the tree looking for a place to insert the object.
	//---------------------------------------------------------------------

	// If there are subnodes..
	if (m_subnode[0] != nullptr)
	{
		// Will be true if subnodes are inserted
		bool inNodes = false;

		// Go through all subnodes
		for (int i = 0; i < 4; ++i)
		{
			// Insert the object into all subnodes that contain it
			if (m_subnode[i]->contains(b))
			{
				m_subnode[i]->insert(b);
				inNodes = true;
			}
		}

		if (inNodes) return;
	}

	//	If NODE_CAPACITY is reached AND max depth is not yet reached
	if (m_index.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH)
	{
		// If no subnodes exist..
		if (m_subnode[0] == nullptr)
		{
			// Make some
			split();

			// Move all indexes of THIS node to the new subnodes.
			for (size_t i = 0; i < m_index.size(); ++i)
			{
				int idex = m_index[i];

				for (int j = 0; j < 4; ++j)
				{
					// If the object fits in the subnode..
					if (m_subnode[j]->contains(static_cast<Circle&>(*object_vec[idex])))
					{
						// Insert it into the subnode.
						m_subnode[j]->insert(static_cast<Circle&>(*object_vec[idex]));
					}
				}
			}

			// Remove all indexes from THIS node
			m_index.clear();
			m_index.shrink_to_fit();
		}

		return;
	}

	// Add objects index to this node
	m_index.emplace_back(b.getIndex());
}

void Quadtree::update()
{

	//---------------------------------------------------------------------
	// Clear the quadtree and insert it with objects.
	//---------------------------------------------------------------------

	m_index.clear();
	m_index.shrink_to_fit();
	delete m_subnode[0];
	delete m_subnode[1];
	delete m_subnode[2];
	delete m_subnode[3];
	m_subnode[0] = nullptr;
	m_subnode[1] = nullptr;
	m_subnode[2] = nullptr;
	m_subnode[3] = nullptr;

	#ifdef BENCHMARK
	int b =  GetTimeMs64();
	#endif

	// Insert objects into the quadtree
	for (size_t i = 0; i < object_vec.size(); ++i)
	{
		insert(static_cast<Circle&>(*object_vec[i]));
	}

	#ifdef BENCHMARK
	int a =  GetTimeMs64()-b;
	std::cout << " - Quadtree update():   " << a << " ms" << std::endl;
	#endif

}

void Quadtree::process()
{
	//---------------------------------------------------------------------
	// Checks if any objects in the node collide with eachother, and if so,
	// resolves those collision.
	//
	// This function should return a vector of all indexes that could be colliding.
	//---------------------------------------------------------------------

	// FIND THE DEEPEST NODE->

	// Are there subnodes?
	if (m_subnode[0] != nullptr)
	{
		m_subnode[0]->process();
		m_subnode[1]->process();
		m_subnode[2]->process();
		m_subnode[3]->process();

		return;
	}

	// THEN DO THIS STUFF UNDERNEATH->

	// Are there objects?
	if (m_index.size() > 0)
	{
		for (size_t i = 0; i < m_index.size(); ++i)
		{
			for (size_t j = i+1; j < m_index.size(); ++j)
			{
				// collision check
				if (static_cast<Circle&>(*object_vec[m_index[i]]).collisionDetection(static_cast<Circle&>(*object_vec[m_index[j]])))
				{
					// resolve collision
					static_cast<Circle&>(*object_vec[m_index[i]]).resolveCollision(static_cast<Circle&>(*object_vec[m_index[j]]));
				}
			}
			//---------------------------------------------------------------------
			// Change the color of the nodes objects to the nodes rect color.
			//---------------------------------------------------------------------
			static_cast<Circle&>(*object_vec[m_index[i]]).changeColor(m_bounds.getColor());
		}
	}
}

void Quadtree::draw() const
{
	if (show_Quadtree) {

		// Draw this nodes boundaries
		m_bounds.draw();

		// Tell every node to draw
		if (m_subnode[0] != nullptr) {
			m_subnode[0]->draw();
			m_subnode[1]->draw();
			m_subnode[2]->draw();
			m_subnode[3]->draw();
		}
	}
}

bool Quadtree::contains(const Circle& b) const
{
	if (m_bounds.contains(b)) return true;
	return false;
}

void Quadtree::setColor(const Color& c)
{
	m_bounds.setColor(c);
}