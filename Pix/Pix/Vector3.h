#pragma once

struct Vector3
{
	float x, y, z;
	Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}
	Vector3(float x, float y, float z)
		: x(x)
		, y(y)
		, z(z)
	{}

	Vector3 operator-() const { return { -x, -y, -z }; }

	Vector3 operator+(const Vector3& b) const { return { x + b.x, y + b.y, z + b.z }; }
	Vector3 operator-(const Vector3& b) const { return { x - b.x, y - b.y, z - b.z }; }

	Vector3 operator*(float s) const { return { x * s, y * s, z * s }; }
	Vector3 operator/(float s) const { return { x / s, y / s, z / s }; }

	Vector3& operator+=(const Vector3& b) { x += b.x, y += b.y, z += b.z; return *this; }
	Vector3& operator-=(const Vector3& b) { x -= b.x, y -= b.y, z -= b.z; return *this; }

	Vector3& operator*=(float s) { x *= s, y *= s, z *= s; return *this; }
	Vector3& operator/=(float s) { x /= s, y /= s, z /= s; return *this; }
};