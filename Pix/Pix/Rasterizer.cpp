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
	mColor = v.Color;
	DrawPoint(v.Position.x + 0.5f, v.Position.y + 0.5f);
}

void Rasterizer::DrawLine(const Vertex& v0, const Vertex& v1)
{
	//lerp from v0 to v1
	//draw along line
	//y = mx + b
	if (MathHelper::CheckEqual(v0.Position, v1.Position))
	{
		DrawPoint(v0);
	}
	else
	{
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
			for (float x = std::floor(startV.Position.x); x <= std::floor(endV.Position.x + 0.5f); ++x)
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
			for (float y = std::floor(startV.Position.y); y <= std::floor(endV.Position.y + 0.5f); ++y)
			{
				float t = (y - startV.Position.y) / (endV.Position.y - startV.Position.y);
				Vertex v = LerpVertex(startV, endV, t);
				DrawPoint(v);
			}
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
		DrawFilledTriangle(v0, v1, v2);
	}
	break;
	}
}

void Rasterizer::DrawFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	std::vector<Vertex> sortedVertices = { v0, v1, v2 };
	std::sort(sortedVertices.begin(), sortedVertices.end(),
		[](const Vertex& lhs, const Vertex& rhs)
		{
			return lhs.Position.y < rhs.Position.y;
		});

	if (MathHelper::CheckEqual(sortedVertices[0].Position.y, sortedVertices[1].Position.y))
	{
		DrawTopFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else if (MathHelper::CheckEqual(sortedVertices[1].Position.y, sortedVertices[2].Position.y))
	{
		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], sortedVertices[2]);
	}
	else
	{
		float t = (sortedVertices[1].Position.y - sortedVertices[0].Position.y) / (sortedVertices[2].Position.y - sortedVertices[0].Position.y);
		Vertex splitVertex = LerpVertex(sortedVertices[0], sortedVertices[2], t);

		DrawBottomFilledTriangle(sortedVertices[0], sortedVertices[1], splitVertex);
		DrawTopFilledTriangle(sortedVertices[1], splitVertex, sortedVertices[2]);
	}
}

void Rasterizer::DrawTopFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex topLeft, topRight;

	if (v0.Position.x < v1.Position.x)
	{
		topLeft = v0;
		topRight = v1;
	}
	else
	{
		topLeft = v1;
		topRight = v0;
	}

	float dy = v2.Position.y - v0.Position.y;
	for (float y = v0.Position.y; y <= v2.Position.y; ++y)
	{
		float t = (y - v0.Position.y) / dy;
		Vertex leftVertex = LerpVertex(topLeft, v2, t);
		Vertex rightVertex = LerpVertex(topRight, v2, t);
		DrawLine(leftVertex, rightVertex);
	}
}

void Rasterizer::DrawBottomFilledTriangle(const Vertex& v0, const Vertex& v1, const Vertex& v2)
{
	Vertex bottomLeft, bottomRight;

	if (v0.Position.x < v1.Position.x)
	{
		bottomLeft = v1;
		bottomRight = v2;
	}
	else
	{
		bottomLeft = v2;
		bottomRight = v1;
	}

	float dy = v2.Position.y - v0.Position.y;
	for (float y = v0.Position.y; y <= v2.Position.y; ++y)
	{
		float t = (y - v0.Position.y) / dy;
		Vertex leftVertex = LerpVertex(v0, bottomLeft, t);
		Vertex rightVertex = LerpVertex(v0, bottomRight, t);
		DrawLine(leftVertex, rightVertex);
	}
}
