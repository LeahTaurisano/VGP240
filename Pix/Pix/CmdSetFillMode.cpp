#include "CmdSetFillMode.h"
#include "Rasterizer.h"

bool CmdSetFillMode::Execute(const std::vector<std::string>& params)
{
	if (params.size() != 1)
	{
		return false;
	}
	
	if (params[0] == "wireframe")
	{
		Rasterizer::Get()->setFillMode(FillMode::Wireframe);
		return true;
	}
	else if (params[0] == "solid")
	{
		Rasterizer::Get()->setFillMode(FillMode::Solid);
		return true;
	}
	else
	{
		return false;
	}
}
