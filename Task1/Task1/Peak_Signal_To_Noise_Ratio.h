#pragma once
#include "Measurer.h"
class Peak_Signal_To_Noise_Ratio : public Measurer
{
public:
	Peak_Signal_To_Noise_Ratio(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};