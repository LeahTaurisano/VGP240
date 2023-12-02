#pragma once
#include "MathHelper.h"
#include <XEngine.h>

struct Vertex
{
	Vector3 Position;
	Vector3 Normal;
	Vector3 WorldPosition;
	Vector3 WorldNormal;
	X::Color Color;
};

inline static Vector3 LerpPosition(const Vector3& v, const Vector3& w, float t)
{
	return MathHelper::Lerp(v, w, t);
}

inline static Vector3 LerpNormal(const Vector3& v, const Vector3& w, float t)
{
	return MathHelper::Normalize(MathHelper::Lerp(v, w, t));
}

inline static X::Color LerpColor(const X::Color& a, const X::Color& b, float t)
{
	return { MathHelper::Lerp(a.r, b.r, t), MathHelper::Lerp(a.g, b.g, t), MathHelper::Lerp(a.b, b.b, t), MathHelper::Lerp(a.a, b.a, t) };
}

inline static Vertex LerpVertex(const Vertex& a, const Vertex& b, float t, bool lerpNormal = false)
{
	Vertex ret;
	ret.Position = LerpPosition(a.Position, b.Position, t);
	ret.WorldPosition = LerpPosition(a.WorldPosition, b.WorldPosition, t);
	ret.Color = LerpColor(a.Color, b.Color, t);
	if (lerpNormal)
	{
		ret.Normal = LerpNormal(a.Normal, b.Normal, t);
		ret.WorldNormal = LerpNormal(a.WorldNormal, b.WorldNormal, t);
	}
	return ret;
}