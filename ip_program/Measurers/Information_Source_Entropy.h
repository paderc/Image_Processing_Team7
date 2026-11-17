#pragma once
#include "Measurer.h"

class Information_Source_Entropy : public Measurer
{
public:
	Information_Source_Entropy(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};
