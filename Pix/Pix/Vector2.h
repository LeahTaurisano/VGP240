#pragma once

struct Vector2
{
	float x, y;
	Vector2()
		: x(0.0f)
		, y(0.0f)
	{}
	Vector2(float x, float y)
		: x(x)
		, y(y)
	{}

	Vector2 operator-() const { return { -x, -y }; }

	Vector2 operator+(const Vector2& b) const { return { x + b.x, y + b.y }; }
	Vector2 operator-(const Vector2& b) const { return { x - b.x, y - b.y }; }

	Vector2 operator*(float s) const { return { x * s, y * s }; }
	Vector2 operator/(float s) const { return { x / s, y / s }; }

	Vector2& operator+=(const Vector2& b) { x += b.x, y += b.y; return *this; }
	Vector2& operator-=(const Vector2& b) { x -= b.x, y -= b.y; return *this; }

	Vector2& operator*=(float s) { x *= s, y *= s; return *this; }
	Vector2& operator/=(float s) { x /= s, y /= s; return *this; }
};