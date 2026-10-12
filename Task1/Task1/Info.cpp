#include <array>
#include <memory>
#include <string_view>

#include "CImg.h"

#include "Brightness_Modifier.h"
#include "Contrast_Modifier.h"
#include "Negative_Modifier.h"
#include "Rotation_Modifier.h"

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
    Negative_Info
    HorizontalFlip_Info,
    VerticalFlip_Info,
    DiagonalFlip_Info,
};
