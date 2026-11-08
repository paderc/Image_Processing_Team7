#include "Standard_Deviation.h"
#include "Variance.h"

void Standard_Deviation::measure_inherited() {
	score = sqrt(variance());
}