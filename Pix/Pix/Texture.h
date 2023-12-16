#pragma once
#include <XEngine.h>

enum class AddressMode : int
{
	Clamp,
	Wrap,
	Mirror,
	Border
};

class Texture
{
public:
	void Load(const std::string& fileName);
	const std::string& GetFileName() const;

	X::Color GetPixel(float u, float v, bool filter, AddressMode mode) const;
	X::Color GetPixel(int x, int y) const;

	int GetWidth() const;
	int GetHeight() const;

private:
	std::string mFileName;
	std::unique_ptr<X::Color[]> mPixels;
	int mWidth = 0;
	int mHeight = 0;
};

