#pragma once
#include "Modifier.h"
class Noise_Maker : public Modifier
{
public:
	Noise_Maker(char* argv[]) : Modifier(argv), harshness(stoi(argv[3])) {}
private:
	void modify_inherited() override;
	unsigned harshness;
};