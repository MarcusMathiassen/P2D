
//-----------------------------------------|
//	AUTHOR: MARCUS MATHIASSEN	   		   |
//	DATE:	03.05.2016	   				   |
//-----------------------------------------|

#include "Quadtree.h"

Quadtree quadtree;

Quadtree::Quadtree()
{
	m_level = 0;
	m_bounds = Rect(Vec2(0,0),Vec2(screen_width,screen_height));
}

Quadtree::Quadtree(int level, const Rect& bounds) : m_level(level), m_bounds(bounds) {}

void Quadtree::init()
{
	m_bounds = Rect(Vec2(0,0),Vec2(screen_width,screen_height));
	m_nodes_vec.clear();
	m_nodes_vec.shrink_to_fit();
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

	// BL
	m_nodes_vec.push_back(uptr<Quadtree>
	(new Quadtree(m_level+1,Rect(Vec2(x,y),Vec2(x+subWidth,y+subHeight)))));

	// BR
	m_nodes_vec.push_back(uptr<Quadtree>
	(new Quadtree(m_level+1,Rect(Vec2(x+subWidth,y),Vec2(x+width,y+subHeight)))));

	// TL
	m_nodes_vec.push_back(uptr<Quadtree>
	(new Quadtree(m_level+1,Rect(Vec2(x,y+subHeight),Vec2(x+subWidth,y+height)))));

	// TR
	m_nodes_vec.push_back(uptr<Quadtree>
	(new Quadtree(m_level+1,Rect(Vec2(x+subWidth,y+subHeight),Vec2(x+width,y+height)))));

	m_nodes_vec[0]->setColor(white);
	m_nodes_vec[1]->setColor(white);
	m_nodes_vec[2]->setColor(white);
	m_nodes_vec[3]->setColor(white);
}

void Quadtree::insert(const Circle& b)
{
	//---------------------------------------------------------------------
	// Go as far down the tree looking for a place to insert the object.
	//---------------------------------------------------------------------

	// If there are subnodes..
	if (m_nodes_vec.size() > 0)
	{
		// Will be true if subnodes are inserted
		bool inNodes = false;

		// Go through all subnodes
		for (size_t i = 0; i < m_nodes_vec.size(); ++i)
		{
			// Insert the object into all subnodes that contain it
			if (m_nodes_vec[i]->contains(b))
			{
				m_nodes_vec[i]->insert(b);
				inNodes = true;
			}
		}

		if (inNodes) return;
	}

	// Add objects index to this node
	m_index_vec.push_back((b.getIndex()));


	//	If NODE_CAPACITY is reached AND max depth is not yet reached
	if (m_index_vec.size() > NODE_CAPACITY && m_level < NODE_MAX_DEPTH)
	{
		// If no subnodes exist..
		if (m_nodes_vec.empty())
		{
			// Make some
			split();

			// Move all indexes of THIS node to the new subnodes.
			for (size_t i = 0; i < m_index_vec.size(); ++i)
			{
				int idex = m_index_vec[i];

				for (size_t j = 0; j < m_nodes_vec.size(); ++j)
				{
					// If the object fits in the subnode..
					if (m_nodes_vec[j]->contains(static_cast<Circle&>(*object_vec[idex])))
					{
						// Insert it into the subnode.
						m_nodes_vec[j]->insert(static_cast<Circle&>(*object_vec[idex]));
					}
				}
			}

			// Remove all indexes from THIS node
			m_index_vec.clear();
			m_index_vec.shrink_to_fit();
		}
	}
}

void Quadtree::update()
{

	//---------------------------------------------------------------------
	// Clear the quadtree and insert it with objects.
	//---------------------------------------------------------------------

	#ifdef BENCHMARK
	int b =  GetTimeMs64();
	#endif

	// Clear the quadstrees
	m_nodes_vec.clear();
	m_nodes_vec.shrink_to_fit();

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
	//---------------------------------------------------------------------

	// Are there subnodes?
	if (m_nodes_vec.size() > 0)
	{
		// Does any of them contain objects?
		for (size_t i = 0; i < m_nodes_vec.size(); ++i)
		{
			m_nodes_vec[i]->process();
		}

		return;
	}

	// Are there objects?
	if (m_index_vec.size() > 0)
	{
		for (size_t i = 0; i < m_index_vec.size(); ++i)
		{
			int idex = m_index_vec[i];

			for (size_t j = i+1; j < m_index_vec.size(); ++j)
			{
				int jdex = m_index_vec[j];

				// collision check
				if (static_cast<Circle&>(*object_vec[idex]).collisionDetection(static_cast<Circle&>(*object_vec[jdex])))
				{
					// resolve collision
					static_cast<Circle&>(*object_vec[idex]).resolveCollision(static_cast<Circle&>(*object_vec[jdex]));
				}
			}

			if (show_Quadtree)
			{
				//---------------------------------------------------------------------
				// Change the color of the nodes objects to the nodes rect color.
				//---------------------------------------------------------------------

				static_cast<Circle&>(*object_vec[idex]).changeColor(m_bounds.getColor());
			}
		}
	}
	// Clear the vector for next frame
	m_index_vec.clear();
	m_index_vec.shrink_to_fit();
}

void Quadtree::draw()
{
	if (show_Quadtree) {

		// Draw this nodes boundaries
		m_bounds.draw();

		// Tell every node to draw
		if (m_nodes_vec.size() > 0) {
			m_nodes_vec[0]->draw();
			m_nodes_vec[1]->draw();
			m_nodes_vec[2]->draw();
			m_nodes_vec[3]->draw();
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

void Quadtree::setRect(const Rect& r)
{
	m_bounds = r;
}