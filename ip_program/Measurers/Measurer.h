#pragma once
#include <string>
#include <iostream>

#include "../Histograms/Histogram_Data.h"
#include "../CImg.h"

using namespace cimg_library;
using namespace std;

class Measurer
{
protected:
	virtual void measure_inherited() = 0;
	virtual string describe();
	int width;
	int height;
	double mean(Intensity_Data data);
	double variance(Intensity_Data data);
	CImg<unsigned char> image;
public:
	Measurer(char* argv[]) : image(), filename(argv[2]) {
		image.load(argv[2]);
		width = image.width();
		height = image.height();

		const string command = argv[1];
		if (command == "--cvariance") unit = " [intensity^2]";
		else if (command == "--cmean" || command == "--cstdev") unit = " [intensity]";
		else if (command == "--cvarcoi") unit = "[1/intensity]";
		else unit = "";
	}
	void measure(bool timer, bool verbose);
	double score = 0.0;
private:
	string filename;
	
	string unit;
};