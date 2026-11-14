#pragma once
#include "Measurer.h"

class Flattening_Coefficient : public Measurer
{
public:
	Flattening_Coefficient(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};
