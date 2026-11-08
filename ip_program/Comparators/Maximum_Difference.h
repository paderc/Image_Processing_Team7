#pragma once
#include "Comparator.h"
class Maximum_Difference : public Comparator
{
public:
	Maximum_Difference(char* argv[]) : Comparator(argv){}
private:
	void compare_inherited() override;
};

