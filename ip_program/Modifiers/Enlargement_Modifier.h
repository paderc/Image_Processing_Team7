#pragma once
#include "Modifier.h"

class Enlargement_Modifier : public Modifier
{
public:
	Enlargement_Modifier(char* argv[]) : Modifier(argv), factor(stof(argv[3])), width(image.width()), height(image.height()), lerp(argv[4][0] == 'T' || argv[4][0] == 't') {}
private:
	unsigned width;
	unsigned height;
	float factor;
	bool lerp;
	void modify_inherited() override;
	void modify_nearest_neighbour();
	void modify_bilinear();
};

