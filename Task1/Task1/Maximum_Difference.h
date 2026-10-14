#pragma once
#include "Measurer.h"
class Maximum_Difference : public Measurer
{
public:
	Maximum_Difference(char* argv[]) : Measurer(argv){}
private:
	void measure_inherited() override;
};

