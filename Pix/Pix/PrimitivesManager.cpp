#include "PrimitivesManager.h"
#include "Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"

extern float gResolutionX;
extern float gResolutionY;

namespace
{
	Matrix4 GetScreenTransform()
	{
		const float hw = gResolutionX * 0.5f;
		const float hh = gResolutionY * 0.5f;
		return Matrix4(
			  hw, 0.0f, 0.0f, 0.0f,
			0.0f,  -hh, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			  hw,   hh, 0.0f, 1.0f
		);
	}

	Vector3 GetFacingNormal(const Vector3& a, const Vector3& b, const Vector3& c)
	{
		const Vector3 v0 = b - a;
		const Vector3 v1 = c - a;
		return MathHelper::Cross(v0, v1);
	}

	bool DrawTriangle(CullMode mode, const Vector3& a, const Vector3& b, const Vector3& c)
	{
		if (mode == CullMode::None)
		{
			return true;
		}

		Vector3 facingNormal = GetFacingNormal(a, b, c);

		switch (mode)
		{
		case CullMode::Back:
		{
			return (facingNormal.z <= 0.0f);
		}
		case CullMode::Front:
		{
			return (facingNormal.z >= 0.0f);
		}
		default:
			break;
		}
		return true;
	}
}

PrimitivesManager::PrimitivesManager()
{
}

PrimitivesManager::~PrimitivesManager()
{
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}

void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
	mCorrectUV = false;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
}

void PrimitivesManager::SetCorrectUV(bool correct)
{
	mCorrectUV = correct;
}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
	mDrawBegin = true;
	mApplyTransform = applyTransform;
	mTopology = topology;
	mVertexBuffer.clear();
	return true;
}

void PrimitivesManager::AddVertex(const Vertex& vertex)
{
	mVertexBuffer.push_back(vertex);
}

bool PrimitivesManager::EndDraw()
{
	if (!mDrawBegin)
	{
		return false;
	}

	switch (mTopology)
	{
	case Topology::Point:
	{
		for (size_t i = 0; i < mVertexBuffer.size(); ++i)
		{
			if (Clipper::Get()->ClipPoint(mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Line:
	{
		for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
		{
			if (Clipper::Get()->ClipLine(mVertexBuffer[i - 1], mVertexBuffer[i]))
			{
				Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
			}
		}
	}
	break;
	case Topology::Triangle:
	{
		const Matrix4 matWorld = MatrixStack::Get()->GetTransform();
		const Matrix4 matView = Camera::Get()->GetViewMatrix();
		const Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
		const Matrix4 matScreen = GetScreenTransform();
		const Matrix4 matNDC = matView * matProj;

		for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
		{
			std::vector<Vertex> triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
			if (mApplyTransform)
			{
				if (MathHelper::CheckEqual(MathHelper::MagnitudeSquared(triangle[0].Normal), 0.0f))
				{
					Vector3 facingNormal = GetFacingNormal(triangle[0].Position, triangle[1].Position, triangle[2].Position);
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						triangle[t].Normal = facingNormal;
					}
				}

				// move the position to world space
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].Position = MathHelper::TransformCoord(triangle[t].Position, matWorld);
					triangle[t].Normal = MathHelper::TransfromNormal(triangle[t].Normal, matWorld);
					triangle[t].WorldPosition = triangle[t].Position;
					triangle[t].WorldNormal = triangle[t].Normal;
				}
				if (triangle[0].Color.z < 0.0f)
				{
					if (mCorrectUV)
					{
						for (size_t t = 0; t < triangle.size(); ++t)
						{
							Vertex& v = triangle[t];
							Vector3 viewPos = MathHelper::TransformCoord(triangle[t].WorldPosition, matView);
							v.Color.x /= viewPos.z;
							v.Color.y /= viewPos.z;
							v.Color.w = 1.0f / viewPos.z;
						}
					}
				}
				else if (Rasterizer::Get()->GetShadeMode() != ShadeMode::Phong)
				{
					//calculate lighting
					LightManager* lm = LightManager::Get();
					for (size_t t = 0; t < triangle.size(); ++t)
					{
						Vertex& v = triangle[t];
						v.Color *= lm->ComputeLightColor(v.WorldPosition, v.WorldNormal);
					}
				}

				// move to NDC space
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].Position = MathHelper::TransformCoord(triangle[t].Position, matNDC);
				}

				if (!DrawTriangle(mCullMode, triangle[0].Position, triangle[1].Position, triangle[2].Position))
				{
					continue;
				}
				for (size_t t = 0; t < triangle.size(); ++t)
				{
					triangle[t].Position = MathHelper::TransformCoord(triangle[t].Position, matScreen);
				}
			}
			if (Clipper::Get()->ClipTriangle(triangle))
			{
				for (size_t t = 2; t < triangle.size(); ++t)
				{
					Rasterizer::Get()->DrawTriangle(triangle[0], triangle[t - 1], triangle[t]);
				}
			}
		}
	}
	break;
	default:
		return false;
	}

	mDrawBegin = false;
	return true;
}
