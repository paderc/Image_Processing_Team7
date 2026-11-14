#pragma once
#include "../CImg.h"
#include "Histogram_Data.h"
#include <string>

using namespace cimg_library;
using namespace std;

class Histogram {
public:
	Histogram(char* argv[], int argc);
	void make(bool timer = false, bool verbose = false);
protected:
	void make_inherited(Histogram_Data& data);
private:
	CImg<unsigned char> image;
	string filename;
	string channel_arg;
	string output_filename;
};
