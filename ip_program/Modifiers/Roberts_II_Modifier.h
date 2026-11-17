#pragma once
#include "Modifier.h"

class Roberts_II_Modifier : public Modifier
{
public:
	Roberts_II_Modifier(char* argv[]) : Modifier(argv) {}
private:
	void modify_inherited() override;
};
