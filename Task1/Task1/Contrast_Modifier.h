#pragma once
#include "CImg.h"

#include "Modifier.h"

using namespace cimg_library;


class Contrast_Modifier : public Modifier {
public:
	int contrast;
	Contrast_Modifier(char* argv[]) : Modifier(argv), contrast(stoi(argv[3])){}
	void modify();
};
