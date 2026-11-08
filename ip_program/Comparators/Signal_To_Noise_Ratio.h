#pragma once
#include "Comparator.h"

class Signal_To_Noise_Ratio : public Comparator
{
public:
	Signal_To_Noise_Ratio(char* argv[]) : Comparator(argv) {}
private:
	void compare_inherited() override;
};

