#pragma once
#include <string>

namespace MathClasses
{
    struct Vector3
    {
        float x, y, z;

        Vector3();
        Vector3(float x, float y, float z);

        std::string ToString() const;

        float Magnitude() const;
        float MagnitudeSqr() const;
        float Dot(Vector3 o) const;
        Vector3 Normalised() const;
        void Normalise();
        Vector3 Cross(Vector3 o) const;



        float DistanceTo(Vector3 o) const;


        friend Vector3 operator+(Vector3 a, Vector3 b);
        friend Vector3 operator-(Vector3 a, Vector3 b);
        friend Vector3 operator*(Vector3 a, float b);
        friend Vector3 operator*(float a, Vector3 b);
        friend Vector3 operator*(Vector3 a, Vector3 b);

        friend bool operator==(Vector3 a, Vector3 b);
        friend bool operator!=(Vector3 a, Vector3 b);
    };
}