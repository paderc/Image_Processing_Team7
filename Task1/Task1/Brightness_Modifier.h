#pragma once
#include "CImg.h";

using namespace cimg_library;

class Brightness_Modifier {
public:
	Brightness_Modifier(){}
	void change(CImg<unsigned char>& image, int brightness);
};