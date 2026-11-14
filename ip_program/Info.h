#pragma once
#include <array>
#include <memory>
#include <string_view>

#include "CImg.h"
#include "Modifiers/Modifier.h"
#include "Comparators/Comparator.h"
#include "Measurers/Measurer.h"

#include "Modifiers/Brightness_Modifier.h"
#include "Modifiers/Contrast_Modifier.h"
#include "Modifiers/Negative_Modifier.h"
#include "Modifiers/Rotation_Modifier.h"
#include "Modifiers/Shrinking_Modifier.h"
#include "Modifiers/Median_Modifier.h"
#include "Modifiers/Geometric_Mean_Modifier.h"
#include "Modifiers/Alpha_Trimmed_Modifier.h"
#include "Modifiers/Enlargement_Modifier.h"
#include "Modifiers/Noise_Maker.h"
#include "Modifiers/PowerTwoThird.h"
#include "Modifiers/Extraction_Details_I.h"
#include "Modifiers/Roberts_II_Modifier.h"

#include "Comparators/Mean_Square_Error.h"
#include "Comparators/Peak_Mean_Square_Error.h"
#include "Comparators/Signal_To_Noise_Ratio.h"
#include "Comparators/Peak_Signal_To_Noise_Ratio.h"
#include "Comparators/Maximum_Difference.h"

#include "Measurers/Variation_Coefficient_I.h"
#include "Measurers/Standard_Deviation.h"
#include "Measurers/Mean_Measure.h"
#include "Measurers/Variance.h"
#include "Measurers/Asymmetry_Coefficient.h"
#include "Measurers/Flattening_Coefficient.h"
#include "Measurers/Variation_Coefficient_II.h"
#include "Measurers/Information_Source_Entropy.h"

using namespace std;
using namespace cimg_library;

template <class T>
using command_factory = shared_ptr<T>(*)(char* argv[]);

template <class T>
shared_ptr<Modifier> make_modifier(char* argv[]) {
    return make_shared<T>(argv);
}

template <class T>
shared_ptr<Comparator> make_comparator(char* argv[]) {
    return make_shared<T>(argv);
}

template <class T>
shared_ptr<Measurer> make_measurer(char* argv[]) {
    return make_shared<T>(argv);
}

template <class T>
struct Command_Info {
	unsigned short required_commands;
	string_view name;
	string_view details;
	string_view description;
	command_factory<T> factory;
};

struct Modifier_Info : Command_Info<Modifier>{};

struct Comparator_Info : Command_Info<Comparator>{};

struct Measurer_Info : Command_Info<Measurer> {};

inline constexpr Modifier_Info Brightness_Info{
    2,
    "--brightness",
    "[filename] [value]",
    "Adjusts brightness of image",
    &make_modifier<Brightness_Modifier>
};
inline constexpr Modifier_Info Contrast_Info{
    2,
    "--contrast",
    "[filename] [value]",
    "Adjusts contrast of image",
    &make_modifier<Contrast_Modifier>
};
inline constexpr Modifier_Info Negative_Info{
    1,
    "--negative",
    "[filename]",
    "Flips all the colors of image",
    &make_modifier<Negative_Modifier>
};
inline constexpr Modifier_Info Shrinking_Info{
    2,
    "--shrink",
    "[filename] [value(0 to 1)]",
    "Shrinks the image by desired factor from 0 to 1",
    &make_modifier<Shrinking_Modifier>
};
inline constexpr Modifier_Info Median_Info{
    3,
    "--median",
    "[filename] [width(0 to 13)] [height(0 to 13)]",
    "Applies a median filter to image, according to given width(0 to 13) and height(0 to 13) of filter rectangle",
    &make_modifier<Median_Modifier>
};
inline constexpr Modifier_Info Geometric_Mean_Info{
    3,
    "--gmean",
    "[filename] [width(0 to 13)] [height(0 to 13)]",
    "Applies a geometric mean filter to image, according to given width(0 to 13) and height(0 to 13) of filter rectangle",
    &make_modifier<Geometric_Mean_Modifier>
};
inline constexpr Modifier_Info HorizontalFlip_Info{
    1,
    "--hflip",
    "[filename]",
    "Flips the image horizontally",
    &make_modifier<Rotation_Modifier>
};
inline constexpr Modifier_Info VerticalFlip_Info{
    1,
    "--vflip",
    "[filename]",
    "Flips the image vertically",
    &make_modifier<Rotation_Modifier>
};
inline constexpr Modifier_Info DiagonalFlip_Info{
    1,
    "--dflip",
    "[filename]",
    "Flips the image diagonally",
    &make_modifier<Rotation_Modifier>
};
inline constexpr Modifier_Info Alpha_Trimmed_Modifier_Info{
    4,
    "--alpha",
    "[filename] [width (0 to 13)] [height (0 to 13)] [elements to skip (. >= 2)]",
    "Trims the pixels in neighbourhood of width and height, according to elements to skip",
    &make_modifier<Alpha_Trimmed_Modifier>
};
inline constexpr Modifier_Info Noise_Maker_Modifier_Info{
    2,
    "--noise",
    "[filename] [harshness (0 to 10)]",
    "Adds noise to the image, according to the specified harshness level",
    &make_modifier<Noise_Maker>
};
inline constexpr Modifier_Info Enlargement_Info{
    2,
    "--enlarge",
    "[filename] [factor >= 1]",
    "Enlarges the image using nearest-neighbor sampling",
    &make_modifier<Enlargement_Modifier>
};
inline constexpr Modifier_Info PowerTwoThird_Info{
	3,
	"--hpower",
	"[filename] [g_min] [g_max]",
	"Applies power two-thirds histogram modification with specified g_min and g_max values",
	&make_modifier<PowerTwoThird>
};
inline constexpr Modifier_Info Extraction_Details_I_Info{
	3,
	"--sexdeti",
	"[filename] [N|NE|E|SE] [universal|opt]",
	"Extracts directional details (N, NE, E, SE) using universal or optimized convolution",
	&make_modifier<Extraction_Details_I>
};
inline constexpr Modifier_Info Roberts_II_Info{
	1,
	"--orobertsii",
	"[filename]",
	"Applies non-linear Roberts II edge detection operator",
	&make_modifier<Roberts_II_Modifier>
};

inline constexpr Comparator_Info Mean_Square_Error_Info{
    2,
    "--mse",
    "[filename 1] [filename 2]",
    "Compares noise with mean square error method",
    &make_comparator<Mean_Square_Error>
};
inline constexpr Comparator_Info Peak_Mean_Square_Error_Info{
    2,
    "--pmse",
    "[filename 1] [filename 2]",
    "Compares noise with peak mean square error method",
    &make_comparator<Peak_Mean_Square_Error>
};
inline constexpr Comparator_Info Signal_To_Noise_Ratio_Info{
    2,
    "--snr",
    "[filename 1] [filename 2]",
    "Compares noise with signal to noise ratio method",
    &make_comparator<Signal_To_Noise_Ratio>
};
inline constexpr Comparator_Info Peak_Signal_To_Noise_Ratio_Info{
    2,
    "--psnr",
    "[filename 1] [filename 2]",
    "Compares noise with peak signal to noise ratio method",
    &make_comparator<Peak_Signal_To_Noise_Ratio>
};
inline constexpr Comparator_Info Maximum_Difference_Info{
    2,
    "--md",
    "[filename 1] [filename 2]",
    "Compares noise with maximum difference method",
    &make_comparator<Maximum_Difference>
};

inline constexpr Measurer_Info Mean_Measure_Info{
	1,
	"--cmean",
	"[filename]",
	"Calculates the mean intensity of the image",
	&make_measurer<Mean_Measure>
};
inline constexpr Measurer_Info Variance_Info{
	1,
	"--cvariance",
	"[filename]",
	"Calculates the variance of the image",
	&make_measurer<Variance>
};
inline constexpr Measurer_Info Standard_Deviation_Info{
	1,
	"--cstdev",
	"[filename]",
	"Calculates the standard deviation of the image",
	&make_measurer<Standard_Deviation>
};
inline constexpr Measurer_Info Variation_Coefficient_I_Info{
	1,
	"--cvarcoi",
	"[filename]",
	"Calculates the variation coefficient I of the image",
	&make_measurer<Variation_Coefficient_I>
};
inline constexpr Measurer_Info Asymmetry_Coefficient_Info{
	1,
	"--casyco",
	"[filename]",
	"Calculates the asymmetry coefficient of the image",
	&make_measurer<Asymmetry_Coefficient>
};
inline constexpr Measurer_Info Flattening_Coefficient_Info{
	1,
	"--cflaco",
	"[filename]",
	"Calculates the flattening coefficient (kurtosis) of the image",
	&make_measurer<Flattening_Coefficient>
};
inline constexpr Measurer_Info Variation_Coefficient_II_Info{
	1,
	"--cvarcoii",
	"[filename]",
	"Calculates the variation coefficient II of the image",
	&make_measurer<Variation_Coefficient_II>
};
inline constexpr Measurer_Info Information_Source_Entropy_Info{
	1,
	"--centropy",
	"[filename]",
	"Calculates the information source entropy of the image",
	&make_measurer<Information_Source_Entropy>
};

inline constexpr array ALL_MODIFIERS{
    Brightness_Info,
    Contrast_Info,
    Negative_Info,
    Shrinking_Info,
    Median_Info,
    Geometric_Mean_Info,
    HorizontalFlip_Info,
    VerticalFlip_Info,
    DiagonalFlip_Info,
    Alpha_Trimmed_Modifier_Info,
    Enlargement_Info,
    Noise_Maker_Modifier_Info,
	PowerTwoThird_Info,
	Extraction_Details_I_Info,
	Roberts_II_Info
};
inline constexpr array ALL_COMPARATORS{
    Mean_Square_Error_Info,
    Peak_Mean_Square_Error_Info,
    Signal_To_Noise_Ratio_Info,
    Peak_Signal_To_Noise_Ratio_Info,
    Maximum_Difference_Info
};
inline constexpr array ALL_MEASURERS{
	Mean_Measure_Info,
	Variance_Info,
	Standard_Deviation_Info,
	Variation_Coefficient_I_Info,
	Asymmetry_Coefficient_Info,
	Flattening_Coefficient_Info,
	Variation_Coefficient_II_Info,
	Information_Source_Entropy_Info
};
