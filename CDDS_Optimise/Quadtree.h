#pragma once
#include "AABB.h"

class Critter;

class Quadtree
{
public:
	static const int m_capacity = 2;

	enum SUBTREE {
		TOP_LEFT = 0,
		TOP_RIGHT,
		BOTTOM_LEFT,
		BOTTOM_RIGHT
	};

public:
	Quadtree();
	Quadtree(AABB boundary);

	~Quadtree();

	void Destroy();

	bool Insert(Critter*); //changed instances of gameobject with critter
	void Subdivide();

	void Update(float deltaTime, Critter critters[]);
	void Draw();

private:
	Critter** m_critters; 
	Quadtree** m_children;

	AABB m_boundary;

};
