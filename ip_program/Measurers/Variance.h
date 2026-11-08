#pragma once

#include "Measurer.h"
#include "Mean_Measure.h"

class Variance : public Measurer
{
public:
	Variance(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};