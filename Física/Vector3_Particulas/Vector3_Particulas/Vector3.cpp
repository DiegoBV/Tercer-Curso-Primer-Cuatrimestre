#include "Vector3.h"

void Vector3::invert()
{
	x = -x;
	y = -y;
	z = -z;
}

float Vector3::squareMagnitude() const
{
	return (x*x + y*y + z*z);
}

float Vector3::magnitude() const
{
	return sqrt(squareMagnitude());
}

void Vector3::operator*=(const float k)
{
	x *= k;
	y *= k;
	z *= k;
}

Vector3 Vector3::operator*(const float k)
{
	return Vector3(x*k, y*k, z*k);
}

void Vector3::normalize()
{
	float m = magnitude();
	x /= m;
	y /= m;
	z /= m;
}

Vector3 Vector3::operator+(const Vector3 & other)
{
	return Vector3(x + other.x, y + other.y, z + other.z);
}

void Vector3::operator+=(const Vector3 & other)
{
	x += other.x;
	y += other.y;
	z += other.z;
}

Vector3 Vector3::operator-(const Vector3 & other)
{
	return Vector3(x - other.x, y - other.y, z - other.z);
}

void Vector3::operator-=(const Vector3 & other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
}

float Vector3::operator*(const Vector3 & v) const
{
	return (x*v.x + y*v.y + z*v.z);
}

float Vector3::dot(const Vector3& v)
{
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::operator%(const Vector3 & v)
{
	return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
}

Vector3 Vector3::vectorProduct(const Vector3 & v)
{
	return Vector3(y*v.z - z * v.y, z*v.x - x * v.z, x*v.y - y * v.x);
}
