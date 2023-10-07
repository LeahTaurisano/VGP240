#pragma once

#include "Vector2.h"
#include "Vector3.h"

class MathHelper
{
public:
	static float MagnitudeSquared(const Vector2& v);
	static float MagnitudeSquared(const Vector3& v);

	static float Magnitude(const Vector2& v);
	static float Magnitude(const Vector3& v);

	static Vector2 Normalize(const Vector2& v);
	static Vector3 Normalize(const Vector3& v);

	static float Dot(const Vector2& v, const Vector2& w);
	static float Dot(const Vector3& v, const Vector3& w);
	
	static Vector3 Cross(const Vector3& v, const Vector3& w);
};