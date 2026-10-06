#pragma once
#include "CImg.h"

using namespace cimg_library;

class Negative_Modifier {
public:
	Negative_Modifier(){}
	void change(CImg<unsigned char>& image);
};