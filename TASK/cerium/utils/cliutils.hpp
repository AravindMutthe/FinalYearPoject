#pragma once

#include <string>

#include "../external/cxxopts.hpp"

namespace cerium
{

auto get_cliparser() -> cxxopts::Options {
    cxxopts::Options options("cerium", "An OpenCV Based, Video Processing Utils Library");

    options
        .positional_help("[optional args]")
        .show_positional_help();

    options
        .allow_unrecognised_options()
        .add_options()
        ("r,record", "Record", cxxopts::value<bool>()->implicit_value("true"))
        ("working_dir", "Working directory", cxxopts::value<std::string>()->default_value("experiments"))
        ("o,output", "output filename (without extension)", cxxopts::value<std::string>()->default_value("output"))
        ("t,timestamp", "add timestamp to filename", cxxopts::value<bool>()->implicit_value("true")->default_value("true"))
        ("cam", "camera id", cxxopts::value<int>()->default_value("0"))
        ("c,channel","channel to extract\nBGR -> 012", cxxopts::value<int>()->default_value("0"))
        ("l,list", "list the files stored in this manner", cxxopts::value<bool>()->implicit_value("true"))
        ("h,help", "print help")
        ;

    return options;
}
    
} // namespace cerium
