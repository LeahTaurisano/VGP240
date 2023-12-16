#include "CmdSetAddressMode.h"
#include "TextureCache.h"

bool CmdSetAddressMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	if (params[0] == "clamp")
	{
		TextureCache::Get()->SetAddressMode(AddressMode::Clamp);
		return true;
	}
	else if (params[0] == "wrap")
	{
		TextureCache::Get()->SetAddressMode(AddressMode::Wrap);
		return true;
	}
	else if (params[0] == "mirror")
	{
		TextureCache::Get()->SetAddressMode(AddressMode::Mirror);
		return true;
	}
	else if (params[0] == "border")
	{
		TextureCache::Get()->SetAddressMode(AddressMode::Border);
		return true;
	}
	else
	{
		return false;
	}
}
