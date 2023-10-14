#include "MathHelper.h"
#include <math.h>

float MathHelper::MagnitudeSquared(const Vector2& v)
{
	return (v.x * v.x) + (v.y * v.y);
}

float MathHelper::MagnitudeSquared(const Vector3& v)
{
	return (v.x * v.x) + (v.y * v.y) + (v.z * v.z);
}

float MathHelper::Magnitude(const Vector2& v)
{
	return sqrtf(MagnitudeSquared(v));
}

float MathHelper::Magnitude(const Vector3& v)
{
	return sqrtf(MagnitudeSquared(v));
}

Vector2 MathHelper::Normalize(const Vector2& v)
{
	return v / Magnitude(v);
}

Vector3 MathHelper::Normalize(const Vector3& v)
{
	return v / Magnitude(v);
}

float MathHelper::Dot(const Vector2& v, const Vector2& w)
{
	return (v.x * w.x) + (v.y * w.y);
}

float MathHelper::Dot(const Vector3& v, const Vector3& w)
{
	return (v.x * w.x) + (v.y * w.y) + (v.z * w.z);
}

Vector3 MathHelper::Cross(const Vector3& v, const Vector3& w)
{
	return { v.y * w.z - v.z * w.y,
			 v.z * w.x - v.x * w.z,
			 v.x * w.y - v.y * w.x };
}

float MathHelper::Lerp(const float& a, const float& b, float t)
{
	return a + (b - a) * t;
}

Vector2 MathHelper::Lerp(const Vector2& v, const Vector2& w, float t)
{
	return { Lerp(v.x, w.x, t), Lerp(v.y, w.y, t) };
}

Vector3 MathHelper::Lerp(const Vector3& v, const Vector3& w, float t)
{
	return { Lerp(v.x, w.x, t), Lerp(v.y, w.y, t), Lerp(v.z, w.z, t) };
}
