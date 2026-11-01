#pragma once
#include "Modifier.h"

class Median_Modifier : public Modifier {
public:
    Median_Modifier(char* argv[])
        : Modifier(argv),
        width(image.width()),
        height(image.height()),
        m(stoi(argv[3])),
        n(stoi(argv[4])) 
    {
        m = clamp(m, 0, 13);
        n = clamp(n, 0, 13);
    }

    void modify_inherited() override;

private:
    unsigned width;
    unsigned height;
    int m;
    int n;
};