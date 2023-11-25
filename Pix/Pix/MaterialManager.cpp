#include "MaterialManager.h"

MaterialManager* MaterialManager::Get()
{
	static MaterialManager sInstance;
	return &sInstance;
}

void MaterialManager::OnNewFrame()
{
	X::Color mAmbient = X::Colors::White;
	X::Color mDiffuse = X::Colors::White;
	X::Color mSpecular = X::Colors::White;
	float mShininess = 1.0f;
}

void MaterialManager::SetMaterialAmbient(const X::Color& ambient)
{
	mAmbient = ambient;
}

void MaterialManager::SetMaterialDiffuse(const X::Color& diffuse)
{
	mDiffuse = diffuse;
}

void MaterialManager::SetMaterialSpecular(const X::Color& specular)
{
	mSpecular = specular;
}

void MaterialManager::SetMaterialShininess(float shininess)
{
	mShininess = shininess;
}

const X::Color MaterialManager::GetMaterialAmbient() const
{
	return mAmbient;
}

const X::Color MaterialManager::GetMaterialDiffuse() const
{
	return mDiffuse;
}

const X::Color MaterialManager::GetMaterialSpecular() const
{
	return mSpecular;
}

float MaterialManager::GetMaterialShininess() const
{
	return mShininess;
}
