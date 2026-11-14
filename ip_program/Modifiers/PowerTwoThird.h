#pragma once
#include "Modifier.h"
#include <string>

class PowerTwoThird : public Modifier
{
public:
	PowerTwoThird(char* argv[]) : Modifier(argv), g_min(std::stoi(argv[3])), g_max(std::stoi(argv[4])) {}
	void modify_inherited() override;
private:
	int g_min = 0;
	int g_max = 255;
};
