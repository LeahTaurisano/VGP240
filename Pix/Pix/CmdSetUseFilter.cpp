#include "CmdSetUseFilter.h"
#include "TextureCache.h"
#include "VariableCache.h"

bool CmdSetUseFilter::Execute(const std::vector<std::string>& params)
{
	if (params.size() < 1)
	{
		return false;
	}

	bool use = VariableCache::Get()->GetBool(params[0]);
	TextureCache::Get()->SetUseFilter(use);
	return true;
}
