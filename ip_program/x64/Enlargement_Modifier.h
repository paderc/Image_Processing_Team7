#pragma once
#include "Modifier.h"

class Enlargement_Modifier : public Modifier
{
public:
	Enlargement_Modifier(char* argv[]) : Modifier(argv), factor(stof(argv[3])), width(image.width()), height(image.height()) {}
private:
	unsigned width;
	unsigned height;
	float factor;
	void modify_inherited() override;
};

