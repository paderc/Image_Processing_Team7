#pragma once
#include "Modifier.h"

class Shrinking_Modifier : public Modifier
{
public:
	unsigned width;
	unsigned height;
	double factor;
	Shrinking_Modifier(char* argv[]) : Modifier(argv), width(image.width()), height(image.height()), factor(stod(argv[3])) {}

	void modify_inherited() override;
};