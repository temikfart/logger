#pragma once

#include <algorithm>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>

namespace fs = std::filesystem;

namespace utils {

using SysClock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<SysClock>;
using MilliSec = std::chrono::milliseconds;

static const int MS_IN_SEC = 1000;

struct Time {
    Time() : timestamp(SysClock::now()) {}

    const TimePoint timestamp;
};

std::string remove_linebreaks(const std::string& str) {
    return str.substr(0, str.rfind('\n'));
}
std::string to_upper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}
std::string to_string(const Time& time) {
    auto tse = std::chrono::duration_cast<MilliSec>(time.timestamp.time_since_epoch());
    int ms = (int)(tse.count() % MS_IN_SEC);
    auto itt = SysClock::to_time_t(time.timestamp);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%F %T.")
       << std::setw(3) << std::setfill('0') << ms;
    return ss.str();
}
std::string to_filepath(const Time& time, const fs::path& dir) {
    auto filename = to_string(time);
    std::replace_if(filename.begin(), filename.end(),
                    [](auto& c) { return (c == ' ' || c == ':'); }, '-');
    filename = filename.substr(0, filename.rfind('.'));
    return (dir.string() + '/' + filename + ".log");
}
std::string get_dirname(const fs::path& path) {
    if (path.string().empty())
        return "";
    if (fs::exists(path))
        return fs::canonical(path).filename();

    auto str = path.string();
    unsigned length = str.length();
    while (length > 0 && (str[length - 1] == '.' || str[length - 1] == '/'))
        length--;
    str = str.substr(0, length);
    return str.substr(str.rfind('/') + 1);
}
fs::path get_parent_path(const fs::path& path) {
    if (fs::exists(path) || path.string().empty())
        return path.parent_path();

    auto str = path.string();
    unsigned length = str.length();
    bool end = false;

    // remove slashes and return path
    if (str[length - 1] == '/') end = true;
    while (length > 0 && str[length - 1] == '/') length--;
    if (end) return str.substr(0, length);

    // remove name and return path
    while (length > 0 && str[length - 1] != '/') length--;
    if (length > 0 && str[length - 1] == '/') length--;
    return str.substr(0, length);
}

class NonCopyable {
public:
    NonCopyable(const NonCopyable& rhs)               = delete;
    NonCopyable(NonCopyable&& rhs)                    = delete;
    NonCopyable& operator=(const NonCopyable& rhs)    = delete;
    NonCopyable& operator=(NonCopyable&& rhs)         = delete;
    ~NonCopyable() = default;

protected:
    NonCopyable() = default;
};

template <typename T>
class Singleton : public NonCopyable {
public:
    Singleton() { instance_ = static_cast<T*>(this); }
    ~Singleton() { instance_ = 0; }

    static T* get_instance() { return instance_; }

private:
    static T* instance_;
};

template<class T>
T* Singleton<T>::instance_ = nullptr;

} // utils
