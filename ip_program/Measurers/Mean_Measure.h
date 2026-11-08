#pragma once
#include "Measurer.h"
class Mean_Measure : public Measurer {
public:
	Mean_Measure(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};