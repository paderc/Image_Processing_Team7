#pragma once
#include "Modifier.h"

class PowerTwoThird : public Modifier
{
public:
	PowerTwoThird(char* argv[]);
	void modify_inherited() override;
private:
	int g_min = 0;
	int g_max = 255;
};
