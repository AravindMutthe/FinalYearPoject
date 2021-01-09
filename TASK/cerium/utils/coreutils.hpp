#pragma once

#include <string>
#include <sstream>
#include <chrono>
#include <iomanip> // for put_time

namespace cerium{

// https://stackoverflow.com/questions/17223096/outputting-date-and-time-in-c-using-stdchrono
// returns the current time stamp
auto get_timestamp() -> std::string {
    // fetch the current date and time
    // auto now = std::chrono::system_clock::now();
    // auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // create the timestsamp
    // std::stringstream tstamp;
    // tstamp << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d-%X");

    // return tstamp.str();

    auto time = std::time(nullptr);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time), "%F_%T"); // ISO 8601 without timezone information.
    auto s = ss.str();
    std::replace(s.begin(), s.end(), ':', '-');

    return s;

}

} // namespace cerium