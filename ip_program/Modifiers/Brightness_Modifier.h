#pragma once
#include <algorithm>

#include "../CImg.h"
#include "Modifier.h"

using namespace std;
using namespace cimg_library;

class Brightness_Modifier : public Modifier {
public:
	int brightness;
	Brightness_Modifier(char* argv[]) : Modifier(argv), brightness(stoi(argv[3])){}

	void modify_inherited() override;
};