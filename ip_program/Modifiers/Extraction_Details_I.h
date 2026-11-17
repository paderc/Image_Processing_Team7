#pragma once
#include "Modifier.h"
#include <array>
#include <string>

class Extraction_Details_I : public Modifier
{
public:
	Extraction_Details_I(char* argv[])
		: Modifier(argv), direction(argv[3]), mode(argv[4]) {}
private:
	void modify_inherited() override;
	void applyUniversal(const std::array<std::array<int, 3>, 3>& mask);
	void applyOptimizedNorth();

	std::string direction; // "N", "NE", "E", "SE"
	std::string mode;      // "universal" or "opt"
};
