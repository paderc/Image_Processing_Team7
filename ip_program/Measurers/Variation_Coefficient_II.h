#pragma once
#include "Measurer.h"

class Variation_Coefficient_II : public Measurer
{
public:
	Variation_Coefficient_II(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};
