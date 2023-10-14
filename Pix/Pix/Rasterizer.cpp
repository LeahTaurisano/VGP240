#include "Rasterizer.h"

Rasterizer* Rasterizer::Get()
{
	static Rasterizer sInstance;
	return &sInstance;
}

void Rasterizer::SetColor(X::Color color)
{
	mColor = color;
}

void Rasterizer::setFillMode(FillMode mode)
{
	mFillMode = mode;
}

void Rasterizer::DrawPoint(int x, int y)
{
	X::DrawPixel(x, y, mColor);
}

void Rasterizer::DrawPoint(const Vertex& v)
{
	X::DrawPixel(v.Position.x, v.Position.y, v.Color);
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	//lerp from v0 to v1
	//draw along line
	//y = mx + b
	float dx = v1.Position.x - v0.Position.x;
	float dy = v1.Position.y - v0.Position.y;

	if (std::abs(dy) < std::abs(dx))
	{
		//normal slope lerp
		Vertex startV, endV;
		if (v0.Position.x < v1.Position.x)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float x = startV.Position.x; x <= endV.Position.x; ++x)
		{
			float t = (x - startV.Position.x) / (endV.Position.x - startV.Position.x);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}
	else
	{
		//normal slope lerp
		Vertex startV, endV;
		if (v0.Position.y < v1.Position.y)
		{
			startV = v0;
			endV = v1;
		}
		else
		{
			startV = v1;
			endV = v0;
		}
		for (float y = startV.Position.y; y <= endV.Position.y; ++y)
		{
			float t = (y - startV.Position.y) / (endV.Position.y - startV.Position.y);
			Vertex v = LerpVertex(startV, endV, t);
			DrawPoint(v);
		}
	}
}

void Rasterizer::DrawTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	switch (mFillMode)
	{
	case FillMode::Wireframe:
	{
		DrawLine(v0, v1);
		DrawLine(v1, v2);
		DrawLine(v2, v0);
	}
	break;
	case FillMode::Solid:
	{
		std::vector<Vertex> sortedVertices = { v0, v1, v2 };
		std::sort(sortedVertices.begin(), sortedVertices.end(),
			[](const Vertex& lhs, const Vertex& rhs)
			{
				return lhs.Position.y < rhs.Position.y;
			});
		DrawFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{

}
