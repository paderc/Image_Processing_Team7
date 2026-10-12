#pragma once
#include <string>
#include <string_view>
#include <iostream>

#include "CImg.h"

using namespace std;
using namespace cimg_library;

class Modifier
{
protected:
	virtual void modify_inherited() = 0;
public:
	string filename, base_name, extension;
	CImg<unsigned char> image;
	Modifier(char* argv[]) : image(), filename() {
		image.load(argv[2]);

		filename = argv[2];
		unsigned dot_index = filename.find_last_of(".");
		extension = filename.substr(dot_index);
		base_name = filename.substr(0, dot_index);

		filename = make_name(base_name, extension);
	}

	void init() {
		filename = make_name(base_name, extension);
	}

	virtual void modify(bool timer, bool verbose) final;
	virtual string make_name(string_view base_name, string_view extension);
	virtual string describe();
	
	virtual ~Modifier() = default;
};

