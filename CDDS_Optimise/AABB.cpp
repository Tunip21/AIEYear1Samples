#include "AABB.h"

AABB::AABB(Vector2 centre, Vector2 halfSize)
	: m_centre(centre), m_halfSize(halfSize)
{

}

bool AABB::contains(Vector2 point)
{
	if (point.x < m_centre.x + m_halfSize.x &&
			point.x > m_centre.x - m_halfSize.x &&
			point.y < m_centre.y + m_halfSize.y &&
			point.y > m_centre.y - m_halfSize.y)
	{
			return true;
	}
	return false;
}

bool AABB::intersects(AABB other)
{
	// if this box's right edge is < other box's left
	if (m_centre.x + m_halfSize.x < other.m_centre.x - other.m_halfSize.x ||
		// or this box's left edge is > other box's right
		m_centre.x - m_halfSize.x > other.m_centre.x + other.m_halfSize.x ||
		// or this box's top edge is < other box's bottom
		m_centre.y + m_halfSize.y < other.m_centre.y - other.m_halfSize.y ||
		// or this box's bottom edge is > other box's top
		m_centre.y - m_halfSize.y > other.m_centre.y + other.m_halfSize.y)
		// then they can't possibly be intersecting
	{
		return false;
	}
	return true;
}
