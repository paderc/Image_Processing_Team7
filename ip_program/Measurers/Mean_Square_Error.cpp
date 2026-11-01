#include "Mean_Square_Error.h"

void Mean_Square_Error::measure_inherited() {
	error = squared_error_sum() / double(image1.size());
}