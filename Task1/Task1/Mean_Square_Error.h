#pragma once
#include "Measurer.h"
class Mean_Square_Error : public Measurer
{
public:
	Mean_Square_Error(char* argv[]) : Measurer(argv) {
	}
private:
	void measure_inherited() override;
};

