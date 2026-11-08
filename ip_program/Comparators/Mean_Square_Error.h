#pragma once
#include "Comparator.h"
class Mean_Square_Error : public Comparator
{
public:
	Mean_Square_Error(char* argv[]) : Comparator(argv) {
	}
private:
	void compare_inherited() override;
};

