#pragma once

#include <algorithm>
#include <string>

namespace utils {

std::string to_upper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}

struct Time {
    Time() : timestamp(std::chrono::system_clock::now()) {}
    const std::chrono::time_point<std::chrono::system_clock> timestamp;
};

std::string to_string(const Time& time) {
    auto itt = std::chrono::system_clock::to_time_t(time.timestamp);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%F %T");
    return ss.str();
}

}
