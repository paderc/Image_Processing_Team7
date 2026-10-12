#include <array>
#include <memory>
#include <string_view>

#include "CImg.h"

#include "Brightness_Modifier.h"
#include "Contrast_Modifier.h"
#include "Negative_Modifier.h"
#include "Rotation_Modifier.h"
#include "Shrinking_Modifier.h"
#include "Median_Modifier.h"
#include "Geometric_Mean_Modifier.h"
using namespace std;
using namespace cimg_library;

template <class T>
using modifier_factory = shared_ptr<T>(*)(char* argv[]);

template <class T>
shared_ptr<Modifier> make_modifier(char* argv[]) {
    return make_shared<T>(argv);
}

struct Info {
    unsigned short required_commands;
    string_view name;
    string_view details;
    string_view description;
    modifier_factory<Modifier> factory;
};

inline constexpr Info Brightness_Info{
    2,
    "--brightness",
    "[filename] [value]",
    "Adjusts brightness of image",
    &make_modifier<Brightness_Modifier>
};
inline constexpr Info Contrast_Info{
    2,
    "--contrast",
    "[filename] [value]",
    "Adjusts contrast of image",
    &make_modifier<Contrast_Modifier>
};
inline constexpr Info Negative_Info{
    1,
    "--negative",
    "[filename]",
    "Flips all the colors of image",
    &make_modifier<Negative_Modifier>
};
inline constexpr Info Shrinking_Info{
    2,
    "--shrink",
    "[filename] [value(0 to 1)]",
    "Shrinks the image by desired factor from 0 to 1",
    &make_modifier<Shrinking_Modifier>
};
inline constexpr Info Median_Info{
    3,
    "--median",
    "[filename] [width(0 to 13)] [height(0 to 13)]",
    "Applies a median filter to image, according to given width(0 to 13) and height(0 to 13) of filter rectangle",
    &make_modifier<Median_Modifier>
};
inline constexpr Info Geometric_Mean_Info{
    3,
    "--gmean",
    "[filename] [width(0 to 13)] [height(0 to 13)]",
    "Applies a geometric mean filter to image, according to given width(0 to 13) and height(0 to 13) of filter rectangle",
    &make_modifier<Geometric_Mean_Modifier>
};

inline constexpr Info HorizontalFlip_Info{
    1,
    "--hflip",
    "[filename]",
    "Flips the image horizontally",
    &make_modifier<Rotation_Modifier>
};

inline constexpr Info VerticalFlip_Info{
    1,
    "--vflip",
    "[filename]",
    "Flips the image vertically",
    &make_modifier<Rotation_Modifier>
};

inline constexpr Info DiagonalFlip_Info{
    1,
    "--dflip",
    "[filename]",
    "Flips the image diagonally",
    &make_modifier<Rotation_Modifier>
};

extern const array ALL_COMMANDS{
    Brightness_Info,
    Contrast_Info,
    Negative_Info,
    Shrinking_Info,
    Median_Info,
    Geometric_Mean_Info
    HorizontalFlip_Info,
    VerticalFlip_Info,
    DiagonalFlip_Info,
};
