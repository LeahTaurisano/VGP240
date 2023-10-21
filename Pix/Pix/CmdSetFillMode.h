#pragma once
#include "Command.h"

class CmdSetFillMode : public Command
{
public:
	const char* GetName() override
	{
		return "SetFillMode";
	}

	const char* GetDescription() override
	{
		return
			"SetFillMode(FillMode)\n"
			"\n"
			"- Sets the fill mode for the rasterizer.";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

