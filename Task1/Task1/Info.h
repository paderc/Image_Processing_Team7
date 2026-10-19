#pragma once
#include <array>
#include <memory>
#include <string_view>

#include "CImg.h"
#include "Modifier.h"
#include "Measurer.h"

#include "Brightness_Modifier.h"
#include "Contrast_Modifier.h"
#include "Negative_Modifier.h"
#include "Rotation_Modifier.h"
#include "Shrinking_Modifier.h"
#include "Median_Modifier.h"
#include "Geometric_Mean_Modifier.h"
#include "Alpha_Trimmed_Modifier.h"
#include "Enlargement_Modifier.h"
#include "Noise_Maker.h"

#include "Mean_Square_Error.h"
#include "Peak_Mean_Square_Error.h"
#include "Signal_To_Noise_Ratio.h"
#include "Peak_Signal_To_Noise_Ratio.h"
#include "Maximum_Difference.h"

using namespace std;
using namespace cimg_library;

template <class T>
using factory = shared_ptr<T>(*)(char* argv[]);

template <class T>
shared_ptr<Modifier> make_modifier(char* argv[]) {
    return make_shared<T>(argv);
}

template <class T>
shared_ptr<Measurer> make_measurer(char* argv[]) {
    return make_shared<T>(argv);
}

struct Modifier_Info {
    unsigned short required_commands;
    string_view name;
    string_view details;
    string_view description;
    factory<Modifier> factory;
};

struct Measurer_Info {
    unsigned short required_commands;
    string_view name;
    string_view details;
    string_view description;
    factory<Measurer> factory;
};

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

inline constexpr Measurer_Info Mean_Square_Error_Info{
    2,
    "--mse",
    "[filename 1] [filename 2]",
    "Compares noise with mean square error method",
    &make_measurer<Mean_Square_Error>
};
inline constexpr Measurer_Info Peak_Mean_Square_Error_Info{
    2,
    "--pmse",
    "[filename 1] [filename 2]",
    "Compares noise with peak mean square error method",
    &make_measurer<Peak_Mean_Square_Error>
};
inline constexpr Measurer_Info Signal_To_Noise_Ratio_Info{
    2,
    "--snr",
    "[filename 1] [filename 2]",
    "Compares noise with signal to noise ratio method",
    &make_measurer<Signal_To_Noise_Ratio>
};
inline constexpr Measurer_Info Peak_Signal_To_Noise_Ratio_Info{
    2,
    "--psnr",
    "[filename 1] [filename 2]",
    "Compares noise with peak signal to noise ratio method",
    &make_measurer<Peak_Signal_To_Noise_Ratio>
};
inline constexpr Measurer_Info Maximum_Difference_Info{
    2,
    "--md",
    "[filename 1] [filename 2]",
    "Compares noise with maximum difference method",
    &make_measurer<Maximum_Difference>
};
inline constexpr Modifier_Info Enlargement_Info{
    2,
    "--enlarge",
    "[filename] [factor >= 1]",
    "Enlarges the image using nearest-neighbor sampling",
    &make_modifier<Enlargement_Modifier>
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
    Noise_Maker_Modifier_Info
};
inline constexpr array ALL_MEASURERS{
    Mean_Square_Error_Info,
    Peak_Mean_Square_Error_Info,
    Signal_To_Noise_Ratio_Info,
    Peak_Signal_To_Noise_Ratio_Info,
    Maximum_Difference_Info
};