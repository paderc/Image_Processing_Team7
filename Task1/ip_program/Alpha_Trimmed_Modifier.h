#pragma once
#include "Modifier.h"
class Alpha_Trimmed_Modifier : public Modifier
{
public:
	Alpha_Trimmed_Modifier(char* argv[]) : Modifier(argv), width(image.width()), height(image.height()), s(stoi(argv[3])), t(stoi(argv[4])), d(stoi(argv[5])) {}
private:
	int width;
	int height;
	int s;
	int t;
	unsigned d;
	void modify_inherited() override;
};

