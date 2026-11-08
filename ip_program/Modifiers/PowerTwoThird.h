#pragma once
#include "Modifier.h"
class PowerTwoThird : public Modifier
{
public:
	PowerTwoThird(char* argv[]) : Modifier(argv), g_min(stoi(argv[3])), g_max(stoi(argv[4])) {}
	void modify_inherited() override;
private:
	int g_min = 0;
	int g_max = 255;
};

