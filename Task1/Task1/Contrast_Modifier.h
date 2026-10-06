#pragma once
#include "CImg.h"

using namespace cimg_library;

class Contrast_Modifier {
public:
	Contrast_Modifier(){}
	void change(CImg<unsigned char>& image, float contrast);
};