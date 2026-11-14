#pragma once
#include "../CImg.h"
#include <limits>
#include <vector>

using namespace std;
using namespace cimg_library;

class Histogram_Data {
public:
	Histogram_Data(CImg<unsigned char>& _image)
		: image(_image), max_value(std::numeric_limits<unsigned char>::max()) {}

	virtual CImg<unsigned char> makeGraph(int width, int height, bool darkMode) = 0;
	virtual ~Histogram_Data() = default;
protected:
	virtual void fill_data() = 0;
	CImg<unsigned char>& image;
	size_t max_value;
};

class Divided_Data : public Histogram_Data {
public:
	Divided_Data(CImg<unsigned char>& _image) : Histogram_Data(_image) {
		spectrum_occurences.resize(max_value + 1);
		for (size_t i = 0; i < max_value + 1; i++) {
			spectrum_occurences.at(i).resize(image.spectrum());
		}
		fill_data();
	}
	vector<vector<unsigned int>> spectrum_occurences;
	CImg<unsigned char> makeGraph(int width, int height, bool darkMode) override;
private:
	void fill_data() override;
};

class Intensity_Data : public Histogram_Data {
public:
	Intensity_Data(CImg<unsigned char>& _image) : Histogram_Data(_image) {
		occurences.resize(max_value + 1);
		fill_data();
	}
	CImg<unsigned char> makeGraph(int width, int height, bool darkMode) override;
	vector<unsigned int> occurences;
private:
	void fill_data() override;
};
