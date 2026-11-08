#pragma once
#include "Comparator.h"
class Peak_Signal_To_Noise_Ratio : public Comparator
{
public:
	Peak_Signal_To_Noise_Ratio(char* argv[]) : Comparator(argv) {}
private:
	void compare_inherited() override;
};