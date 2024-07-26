#include "Quadtree.h"
#include "AABB.h"
#include <memory>

#include "Critter.h"

Quadtree::Quadtree()
: m_critters(nullptr), m_children(nullptr)
{
	m_boundary.m_halfSize.x = 800 / 2;
	m_boundary.m_halfSize.y = 450 / 2;
	m_boundary.m_centre = m_boundary.m_halfSize;
}

Quadtree::Quadtree(AABB boundary)
: m_boundary(boundary), m_critters(nullptr), m_children(nullptr)
{
}

Quadtree::~Quadtree()
{
	if (m_children != nullptr) 
	{
		for (int i = 0; i < 4; i++) 
		{
			if (m_children[i] != nullptr)
				delete m_children[i];
		}
		delete m_children;
		m_children = nullptr;
	}

	if (m_critters != nullptr) 
	{
		for (int i = 0; i < m_capacity; i++) 
		{
			if (m_critters[i] != nullptr)
				delete m_critters[i];
		}
		delete m_critters;
		m_critters = nullptr;
	}
}

void Quadtree::Destroy()
{
	if (m_children != nullptr)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_children[i] != nullptr)
				delete m_children[i];
		}
		delete m_children;
		m_children = nullptr;
	}

	if (m_critters != nullptr)
	{
		for (int i = 0; i < m_capacity; i++)
		{
			if (m_critters[i] != nullptr)
				delete m_critters[i];
		}
		delete m_critters;
		m_critters = nullptr;
	}
}

void Quadtree::Subdivide()
{
	m_children = new Quadtree*[4];

	Vector2 qSize{ m_boundary.m_halfSize.x / 2, m_boundary.m_halfSize.y / 2 };

	Vector2 qCentre{ m_boundary.m_centre.x - qSize.x, m_boundary.m_centre.y - qSize.y };
	m_children[TOP_LEFT] = new Quadtree(AABB(qCentre, qSize));

	qCentre = Vector2{ m_boundary.m_centre.x + qSize.x, m_boundary.m_centre.y - qSize.y };
	m_children[TOP_RIGHT] = new Quadtree(AABB(qCentre, qSize));

	qCentre = Vector2{ m_boundary.m_centre.x - qSize.x, m_boundary.m_centre.y + qSize.y };
	m_children[BOTTOM_LEFT] = new Quadtree(AABB(qCentre, qSize));

	qCentre = Vector2{ m_boundary.m_centre.x + qSize.x, m_boundary.m_centre.y + qSize.y };
	m_children[BOTTOM_RIGHT] = new Quadtree(AABB(qCentre, qSize));

	if (m_critters != nullptr) {
		for (int i = 0; i < m_capacity; i++) {
			if (m_critters[i] == nullptr) 
				continue;

			// find a subtree to insert the object into
			for (int j = 0; j < 4; j++) {
				if (m_children[j]->Insert(m_critters[i]) == true)
					break;
			}
			// remove the gameobject from the objects array for this node
			// (don't delete it, just set it to null - the object still needs to 
			// exist in the child node)
			m_critters[i] = nullptr;
		}
		// all of the objects that were stored in this node are now stored in the 
		// child nodes, so delete the objects array.
		delete m_critters;
		m_critters = nullptr;
	}
}

bool Quadtree::Insert(Critter* gameObject)
{
	//if (m_boundary.contains(gameObject.m_bounds.m_centre) == false)
	if (m_boundary.contains(gameObject->m_position) == false)
	{
		return false;
	}

	// if this node doesn't have children (hasn't been subdivided), then try to
	// insert the gameobject in this node's object list
	if (m_children == nullptr)
	{
		// is the objects array full?
		if (m_critters == nullptr)
		{
			m_critters = new Critter* [m_capacity];
			memset(m_critters, 0, sizeof(Critter*) * m_capacity);
		}
		if (m_critters[m_capacity - 1] == nullptr) 
		{
			// we have at least 1 free space, so step through the array and look for somewhere
			// to insert the data
			for (int i = 0; i < m_capacity; i++) 
			{
				if (m_critters[i] == nullptr) 
				{
					m_critters[i] = gameObject;
					return true;
				}
			}
		}

		// if we coudldn't insert it in the objects array (ie, it was full), then
		// subdivide this node
		Subdivide();
	}

	// we couldn't insert the gameobject into this node, so find a child node to insert into
	for (int i = 0; i < 4; i++) 
	{
		if (m_children[i]->Insert(gameObject) == true)
			return true;
	}

	return false;	// should never happen
}

void Quadtree::Update(float deltaTime, Critter critters[])
{
	/*for (int n = 0; n != sizeof(critters); ++n)
	{
		if (critters[n].GetX() != m_critters[n]->GetX() && critters[n].GetX() != m_critters[n]->GetX())
		{
			return;
		}
	}*/
}



void Quadtree::Draw()
{
	DrawLine(
		m_boundary.m_centre.x - m_boundary.m_halfSize.x, m_boundary.m_centre.y - m_boundary.m_halfSize.y,
		m_boundary.m_centre.x + m_boundary.m_halfSize.x, m_boundary.m_centre.y - m_boundary.m_halfSize.y, RED);
	DrawLine(
		m_boundary.m_centre.x - m_boundary.m_halfSize.x, m_boundary.m_centre.y + m_boundary.m_halfSize.y - 1,
		m_boundary.m_centre.x + m_boundary.m_halfSize.x, m_boundary.m_centre.y + m_boundary.m_halfSize.y - 1, RED);
	DrawLine(
		m_boundary.m_centre.x - m_boundary.m_halfSize.x + 1, m_boundary.m_centre.y + m_boundary.m_halfSize.y,
		m_boundary.m_centre.x - m_boundary.m_halfSize.x + 1, m_boundary.m_centre.y - m_boundary.m_halfSize.y, RED);
	DrawLine(
		m_boundary.m_centre.x + m_boundary.m_halfSize.x, m_boundary.m_centre.y + m_boundary.m_halfSize.y,
		m_boundary.m_centre.x + m_boundary.m_halfSize.x, m_boundary.m_centre.y - m_boundary.m_halfSize.y, RED);

	if (m_children != nullptr) {
		for (int i = 0; i < 4; i++) {
			m_children[i]->Draw();
		}
	}

	if (m_critters != nullptr) {
		for (int i = 0; i < m_capacity; i++) {
			if (m_critters[i] != nullptr)
				m_critters[i]->Draw();
		}
	}
}