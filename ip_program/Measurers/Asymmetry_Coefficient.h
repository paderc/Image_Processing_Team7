#pragma once
#include "Measurer.h"


class Asymmetry_Coefficient : public Measurer
{
public:
	Asymmetry_Coefficient(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};

