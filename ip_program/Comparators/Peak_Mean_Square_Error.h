#pragma once
#include "Comparator.h"

class Peak_Mean_Square_Error : public Comparator
{
public:
	Peak_Mean_Square_Error(char* argv[]) : Comparator(argv){}
	void compare_inherited() override;
	string describe() override;
};

