#pragma once

#include "Vector3.h"
//#include "Matrix3.h"

#include <limits>
#include <vector>
class AABB
{
public:
	AABB();
	AABB(const MathClasses::Vector3& min, const MathClasses::Vector3& max);
	MathClasses::Vector3 Center() const;
	MathClasses::Vector3 Extents() const;
	std::vector<MathClasses::Vector3> Corners() const;
	void Fit(const MathClasses::Vector3* points, unsigned int count);
	void Fit(const std::vector<MathClasses::Vector3>& points);
	bool Overlaps(const MathClasses::Vector3& p) const;
	bool Overlaps(const AABB& other) const;
	MathClasses::Vector3 ClosestPoint(const MathClasses::Vector3& p) const;
	//void SetToTransformedBox(const MathClasses::Matrix3& m);
	bool isEmpty() const;
	void empty();

	constexpr float Min(float a, float b) const;
	constexpr float Max(float a, float b) const;

	MathClasses::Vector3 Min(const MathClasses::Vector3& a, const MathClasses::Vector3 b) const;
	MathClasses::Vector3 Max(const MathClasses::Vector3& a, const MathClasses::Vector3 b) const;

	constexpr float clamp(float t, float a, float b) const;
	MathClasses::Vector3 clamp(const MathClasses::Vector3& t, const MathClasses::Vector3& a, const MathClasses::Vector3& b) const;

	MathClasses::Vector3 min, max;
	float inf = std::numeric_limits<float>::infinity();

};
