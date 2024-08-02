#include "Vector3.h"
#include <cmath>

MathClasses::Vector3::Vector3()
	: x{ 0.f }, y{ 0.f }, z{ 0.f }
{
}

MathClasses::Vector3::Vector3(float x, float y, float z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}

std::string MathClasses::Vector3::ToString() const
{
	return std::string("[" + std::to_string(x) + "]\n[" + std::to_string(y) + "]\n[" + std::to_string(z) + "]\n");
}

float MathClasses::Vector3::Magnitude() const
{
	return sqrt(x * x + y * y + z * z);
}

float MathClasses::Vector3::MagnitudeSqr() const
{
	return x * x + y * y + z * z;
}

float MathClasses::Vector3::Dot(Vector3 o) const
{
	return x * o.x + y * o.y + z * o.z;
}

MathClasses::Vector3 MathClasses::Vector3::Normalised() const
{
	float thisMagnitude = Magnitude();
	return Vector3(x / thisMagnitude, y / thisMagnitude, z / thisMagnitude);
}

void MathClasses::Vector3::Normalise()
{
	float thisMagnitude = Magnitude();
	x = x / thisMagnitude;
	y = y / thisMagnitude;
	z = z / thisMagnitude;
}

MathClasses::Vector3 MathClasses::Vector3::Cross(Vector3 o) const
{
	return Vector3(y * o.z - z * o.y, z * o.x - x * o.z, x * o.y - y * o.x);
}



float MathClasses::Vector3::DistanceTo(Vector3 o) const
{
	return Vector3(x - o.x, y - o.y, 1).Magnitude();
}

MathClasses::Vector3 MathClasses::operator + (Vector3 a, Vector3 b)
{
	return Vector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

MathClasses::Vector3 MathClasses::operator - (Vector3 a, Vector3 b)
{
	return Vector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

MathClasses::Vector3 MathClasses::operator * (Vector3 a, float b)
{
	return Vector3(a.x * b, a.y * b, a.z * b);
}

MathClasses::Vector3 MathClasses::operator * (float a, Vector3 b)
{
	return Vector3(a * b.x, a * b.y, a * b.z);
}

MathClasses::Vector3 MathClasses::operator*(Vector3 a, Vector3 b)
{
	return Vector3(a.x * b.x, a.y * b.y, a.z * b.z); //newly added, may be wrong
}

bool MathClasses::operator == (Vector3 a, Vector3 b)
{
	float diff[3]
	{
		std::fabsf(a.x - b.x),
		std::fabsf(a.y - b.y),
		std::fabsf(a.z - b.z)
	};
	for (float d : diff)
	{
		if (d > 0.00001f)
		{
			return false;
		}
	}
	return true;
}

bool MathClasses::operator != (Vector3 a, Vector3 b)
{

	return !(a == b);
	//float diff[3]
	//{
	//	std::fabsf(a.x - b.x),
	//	std::fabsf(a.y - b.y),
	//	std::fabsf(a.z - b.z)
	//};
	//for (float d : diff)
	//{
	//	if (d > 0.00001f)
	//	{
	//		return true;
	//	}
	//}
	//return false;
}
