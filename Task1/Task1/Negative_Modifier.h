#pragma once
#include "CImg.h"

#include "Modifier.h"

using namespace cimg_library;

class Negative_Modifier : public Modifier{
public:
	Negative_Modifier(char* argv[]) : Modifier(argv) {}
	void modify();
};