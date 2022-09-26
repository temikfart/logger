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

}
