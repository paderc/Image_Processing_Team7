#pragma once
#include "Measurer.h"
#include "Standard_Deviation.h"
class Variation_Coefficient_I : public Measurer
{
public:
	Variation_Coefficient_I(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};

