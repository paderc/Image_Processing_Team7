#include <array>
#include <memory>
#include <string_view>

#include "CImg.h"

#include "Modifier.h"
#include "Brightness_Modifier.h"

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

extern const array ALL_COMMANDS{
    Brightness_Info,
};