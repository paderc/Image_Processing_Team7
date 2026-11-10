#include "Standard_Deviation.h"
#include "Variance.h"

void Standard_Deviation::measure_inherited() {
	Intensity_Data data(image);
	score = sqrt(variance(data));
}