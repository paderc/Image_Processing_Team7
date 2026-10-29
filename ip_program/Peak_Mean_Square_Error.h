#pragma once
#include "Measurer.h"

class Peak_Mean_Square_Error : public Measurer
{
public:
	Peak_Mean_Square_Error(char* argv[]) : Measurer(argv){}
	void measure_inherited() override;
	string describe() override;
};

