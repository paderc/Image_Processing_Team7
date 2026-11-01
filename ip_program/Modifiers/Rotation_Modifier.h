#pragma once
#include <algorithm>

#include "../CImg.h"

#include "Modifier.h"

using namespace std;
using namespace cimg_library;

class Rotation_Modifier : public Modifier
{
public:
	string direction;

	Rotation_Modifier(char* argv[]) : Modifier(argv), direction(argv[1]) {}

	void modify_inherited() override;
};

