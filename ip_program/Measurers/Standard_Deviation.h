#pragma once
#include "Measurer.h"

class Standard_Deviation : public Measurer
{
public:
	Standard_Deviation(char* _argv[]) : Measurer(_argv) {}
private:
	void measure_inherited() override;
};	