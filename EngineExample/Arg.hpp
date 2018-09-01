#pragma once

#include <string>

struct Arg {
    Arg(int argc, char *argv[]);

    int width;
    int height;
    std::string sceneName;
};