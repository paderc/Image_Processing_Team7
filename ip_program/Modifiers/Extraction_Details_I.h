#pragma once
#include "Modifier.h"
#include <string>

class Extraction_Details_I : public Modifier
{
public:
	Extraction_Details_I(char* argv[])
		: Modifier(argv), direction(argv[3]), mode(argv[4]) {}

	static void applyUniversal(CImg<unsigned char>& image, const CImg<double>& mask);
private:
	void modify_inherited() override;
	void applyOptimizedNorth();

	std::string direction; // "N", "NE", "E", "SE"
	std::string mode;      // "universal" or "opt"
};
