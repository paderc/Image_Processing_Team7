#pragma once
#include "Measurer.h"
#include "Standard_Deviation.h"
class Variation_Coefficient_I : public Measurer
{
public:
	Variation_Coefficient_I(char* argv[]) : Measurer(argv) {
		Standard_Deviation standard_deviation(argv);
		standard_deviation.measure(false, false);
		std_dev = standard_deviation.score;
	}
private:
	void measure_inherited() override;
	double std_dev = 0.0;
};

