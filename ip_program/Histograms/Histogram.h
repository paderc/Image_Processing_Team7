#include "../CImg.h"
#include "Histogram_Data.h"

using namespace cimg_library;
using namespace std;

class Histogram {
public:
	Histogram(char* argv[]) : image() {}
	void make();
protected:
	void make_inherited(Histogram_Data& data);
private:
	CImg<unsigned char> image;
};