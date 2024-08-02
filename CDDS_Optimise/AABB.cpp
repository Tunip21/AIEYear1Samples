#include "AABB.h"
#include <iostream>

AABB::AABB()
{

}

AABB::AABB(const MathClasses::Vector3& min, const MathClasses::Vector3& max)
	: min(min), max(max)
{

}

MathClasses::Vector3 AABB::Center() const
{
	return (min + max) * 0.5f;
}

MathClasses::Vector3 AABB::Extents() const
{
	return { abs(max.x - min.x) * 0.5f, abs(max.y - min.y) * 0.5f , 0 };
}

std::vector<MathClasses::Vector3> AABB::Corners() const
{
	std::vector<MathClasses::Vector3> corners(4);
	corners[0] = min;
	corners[1] = { min.x, max.y, 1 };
	corners[2] = max;
	corners[3] = { max.x, min.y, 1 };
	return corners;
}

void AABB::Fit(const MathClasses::Vector3* points, unsigned int count)
{
	// invalidate the extents
	min = { FLT_MAX, FLT_MAX, 1 };
	max = { FLT_MIN, FLT_MIN, 1 };
	// find min and max of the points
	for (unsigned int i = 0; i < count; ++i, ++points)
	{
		min = Min(min, *points); //changed from ::min
		max = Max(max, *points);
	}
}

void AABB::Fit(const std::vector<MathClasses::Vector3>& points)
{
	// invalidate the extents
	min = { FLT_MAX, FLT_MAX, 1 };
	max = { -FLT_MAX, -FLT_MAX, 1 }; // NB These have -ve signs!
	// find min and max of the points
	for (auto& p : points)
	{
		min = Min(min, p);
		max = Max(max, p);
	}
}

bool AABB::Overlaps(const MathClasses::Vector3& p) const
{
	// test for not overlapped as it exits faster
	return !(p.x < min.x || p.y < min.y || p.x > max.x || p.y > max.y);
}

bool AABB::Overlaps(const AABB& other) const
{
	// test for not overlapped as it exits faster
	return !(max.x < other.min.x || max.y < other.min.y || min.x > other.max.x || min.y > other.max.y);
}

MathClasses::Vector3 AABB::ClosestPoint(const MathClasses::Vector3& p) const
{
	return clamp(p, min, max); //changed from  return clamp(p, min, max);
}

//void AABB::SetToTransformedBox(const MathClasses::Matrix3& m)
//{
//	// If we're empty, then exit (an empty box defined as having the min/max 
//	// set to infinity)
//	if (isEmpty())
//	{
//		empty();
//		return;
//	}
//
//	// Examine each of the nine matrix elements
//	// and compute the new AABB
//	if (m.m11 > 0.0f)
//	{
//		min.x += m.m11 * min.x;
//		max.x += m.m11 * max.x;
//	}
//	else
//	{
//		min.x += m.m11 * max.x;
//		max.x += m.m11 * min.x;
//	}
//
//	if (m.m12 > 0.0f)
//	{
//		min.y += m.m12 * min.x;
//		max.y += m.m12 * max.x;
//	}
//	else
//	{
//		min.y += m.m12 * max.x;
//		max.y += m.m12 * min.x;
//	}
//	if (m.m13 > 0.0f)
//	{
//		min.z += m.m13 * min.x;
//		max.z += m.m13 * max.x;
//	}
//	else
//	{
//		min.z += m.m13 * max.x;
//		max.z += m.m13 * min.x;
//	}
//	if (m.m21 > 0.0f)
//	{
//		min.z += m.m21 * min.x;
//		max.z += m.m21 * max.x;
//	}
//	else
//	{
//		min.z += m.m21 * max.x;
//		max.z += m.m21 * min.x;
//	}
//	if (m.m22 > 0.0f)
//	{
//		min.z += m.m22 * min.x;
//		max.z += m.m22 * max.x;
//	}
//	else
//	{
//		min.z += m.m22 * max.x;
//		max.z += m.m22 * min.x;
//	}
//	if (m.m23 > 0.0f)
//	{
//		min.z += m.m23 * min.x;
//		max.z += m.m23 * max.x;
//	}
//	else
//	{
//		min.z += m.m23 * max.x;
//		max.z += m.m23 * min.x;
//	}
//	if (m.m31 > 0.0f)
//	{
//		min.z += m.m31 * min.x;
//		max.z += m.m31 * max.x;
//	}
//	else
//	{
//		min.z += m.m31 * max.x;
//		max.z += m.m31 * min.x;
//	}
//	if (m.m32 > 0.0f)
//	{
//		min.z += m.m32 * min.x;
//		max.z += m.m32 * max.x;
//	}
//	else
//	{
//		min.z += m.m32 * max.x;
//		max.z += m.m32 * min.x;
//	}
//	if (m.m33 > 0.0f)
//	{
//		min.z += m.m33 * min.x;
//		max.z += m.m33 * max.x;
//	}
//	else
//	{
//		min.z += m.m33 * max.x;
//		max.z += m.m33 * min.x;
//	}
//}

bool AABB::isEmpty() const
{
	return(min.x == inf || max.x == inf);
}

void AABB::empty()
{
	min.x = min.y = min.z = max.x = max.y = max.z = inf;
}

constexpr float AABB::Min(float a, float b) const
{
	return a < b ? a : b;
}



constexpr float AABB::Max(float a, float b) const
{
	return a > b ? a : b;
}

MathClasses::Vector3 AABB::Min(const MathClasses::Vector3& a, const MathClasses::Vector3 b) const
{
	return { Min(a.x, b.x), Min(a.y, b.y) , 1 };
}

MathClasses::Vector3 AABB::Max(const MathClasses::Vector3& a, const MathClasses::Vector3 b) const
{
	return { Max(a.x,b.x), Max(a.y, b.y) , 1 };
}

constexpr float AABB::clamp(float t, float a, float b) const
{
	return Max(a, Min(b, t));
}

MathClasses::Vector3 AABB::clamp(const MathClasses::Vector3& t, const MathClasses::Vector3& a, const MathClasses::Vector3& b) const
{
	return Max(a, Min(b, t));
}