#pragma once
#include "Command.h"

class CmdSetCorrectUV : public Command
{
public:
	const char* GetName() override
	{
		return "SetCorrectUV";
	}

	const char* GetDescription() override
	{
		return
			"SetCorrectUV(correct)\n"
			"\n"
			"- use correct uv.\n";
	}

	bool Execute(const std::vector<std::string>& params) override;
};

