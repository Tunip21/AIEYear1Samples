#pragma once
#include <raylib.h>

class AABB
{
public:
	AABB(); 
	AABB(Vector2 centre, Vector2 halfSize);

	bool contains(Vector2 point);
	bool intersects(AABB other);

	Vector2 m_centre;
	Vector2 m_halfSize;
};
