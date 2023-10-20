#pragma once

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cctype>
#include <filesystem>
#include <iomanip>
#include <string>

namespace fs = std::filesystem;

namespace logger::utils {

using SysClock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<SysClock>;
using MilliSec = std::chrono::milliseconds;

static const int MS_IN_SEC = 1000;

struct Time {
public:
    Time() : timestamp_(SysClock::now()) {}

    std::string to_string(bool is_ISO_format = false) const {
        auto tse = std::chrono::duration_cast<MilliSec>(timestamp_.time_since_epoch());
        int ms = (int) (tse.count() % MS_IN_SEC);
        auto itt = SysClock::to_time_t(timestamp_);
        std::ostringstream ss;
        if (is_ISO_format)
            ss << std::put_time(gmtime(&itt), "%Y-%m-%dT%H:%M:%S.")
               << std::setw(3) << std::setfill('0') << ms << "Z";
        else
            ss << std::put_time(gmtime(&itt), "%Y-%m-%d %H:%M:%S.")
               << std::setw(3) << std::setfill('0') << ms;
        return ss.str();
    }

private:
    const TimePoint timestamp_;
};

inline std::string ltrim(std::string str) {
    str.erase(str.begin(),
              std::find_if(str.begin(), str.end(), [](unsigned char ch) {
                  return !std::isspace(ch);
              }));
    return str;
}
inline std::string rtrim(std::string str) {
    str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
                  return !std::isspace(ch);
              }).base(),
              str.end());
    return str;
}
inline std::string trim(const std::string& str) {
    return ltrim(rtrim(str));
}
inline std::string to_upper(const std::string_view& str) {
    std::string res(str);
    std::transform(res.begin(), res.end(), res.begin(), toupper);
    return res;
}
inline std::string to_lower(const std::string_view& str) {
    std::string res(str);
    std::transform(res.begin(), res.end(), res.begin(), tolower);
    return res;
}
inline std::string to_filepath(const Time& time, const fs::path& dir) {
    auto filename = time.to_string();
    std::replace_if(filename.begin(), filename.end(),
                    [](auto& c) { return (c == ' ' || c == ':'); }, '-');
    filename = filename.substr(0, filename.rfind('.'));
    return (dir.string() + '/' + filename + ".log");
}
inline std::string get_dirname(const fs::path& path) {
    if (path.string().empty())
        return "";
    if (fs::exists(path)) {
        if (fs::is_directory(path)) return fs::canonical(path).filename().string();
        else return fs::canonical(path.parent_path()).filename().string();
    }

    std::string str = path.string();
    unsigned length = str.length();
    while (length > 0 && (str[length - 1] == '.' || str[length - 1] == '/'))
        length--;
    str = str.substr(0, length);
    return str.substr(str.rfind('/') + 1);
}
inline fs::path get_parent_path(const fs::path& path) {
    if (fs::exists(path) || path.string().empty())
        return path.parent_path();

    std::string str = path.string();
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
inline bool maybe_regular_file(const fs::path& path) {
    if (path.empty())
        return false;
    if (fs::exists(path))
        return fs::is_regular_file(path);

    std::string str = path.string();
    unsigned length = str.length();

    if (str[length - 1] == '/') length--;
    if (str[length - 1] == '.') return false;

    // remove slashes
    while (length > 0 && str[length - 1] == '/') length--;
    // remove symbols after the dot or slash
    while (length > 0 && std::isalpha(str[length - 1])) length--;

    return (str[length - 1] == '.');
}

class NonCopyable {
public:
    NonCopyable(const NonCopyable& rhs) = delete;
    NonCopyable(NonCopyable&& rhs) = delete;
    NonCopyable& operator=(const NonCopyable& rhs) = delete;
    NonCopyable& operator=(NonCopyable&& rhs) = delete;
    ~NonCopyable() = default;

protected:
    NonCopyable() = default;
};

template<typename T>
class Singleton : public NonCopyable {
public:
    Singleton() { instance_ = static_cast<T*>(this); }
    ~Singleton() { instance_ = 0; }

protected:
    static T* get_instance() { return instance_; }

private:
    static T* instance_;
};

template<class T>
T* Singleton<T>::instance_ = nullptr;

} // logger
