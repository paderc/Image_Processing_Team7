#pragma once
#include "Measurer.h"

class Signal_To_Noise_Ratio : public Measurer
{
public:
	Signal_To_Noise_Ratio(char* argv[]) : Measurer(argv) {}
private:
	void measure_inherited() override;
};

