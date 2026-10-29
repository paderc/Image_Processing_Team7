#pragma once
#include <string>
#include <iostream>

#include "CImg.h"

using namespace cimg_library;
using namespace std;

class Measurer
{
protected:
	virtual void measure_inherited() = 0;
	virtual string describe();
	int width;
	int height;
	double squared_error_sum() const;
	double reference_peak() const;
public:
	Measurer(char* argv[]) : image1(), image2(), error(0), filename1(argv[2]), filename2(argv[3]) {
		image1.load(argv[2]);
		image2.load(argv[3]);
		if (image1.width() != image2.width() || image1.height() != image2.height()) throw EXCEPTION_FLT_INVALID_OPERATION;
		width = image1.width();
		height = image1.height();
		const string command = argv[1];
		if (command == "--snr" || command == "--psnr") unit = " [dB]";
		else if (command == "--mse") unit = " [intensity^2]";
		else if (command == "--md") unit = " [intensity]";
		else unit = "";
	}
	void measure(bool timer, bool verbose);
	double error;
	string filename1;
	CImg<unsigned char> image1;
	string filename2;
	CImg<unsigned char> image2;
	string unit;
};

