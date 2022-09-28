#pragma once

#include <algorithm>
#include <string>

namespace fs = std::filesystem;

namespace utils {

struct Time {
    Time() : timestamp(std::chrono::system_clock::now()) {}

    const std::chrono::time_point<std::chrono::system_clock> timestamp;
};

std::string to_upper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), toupper);
    return str;
}
std::string to_string(const Time& time) {
    auto itt = std::chrono::system_clock::to_time_t(time.timestamp);
    std::ostringstream ss;
    ss << std::put_time(gmtime(&itt), "%F %T");
    return ss.str();
}
std::string to_filename(const Time& time, const fs::path& dir) {
    auto filename = to_string(time);
    std::replace_if(filename.begin(), filename.end(),
                    [](auto& c) { return (c == ' ' || c == ':'); }, '-');
    filename = dir.string() + '/' + filename + ".log";
    return filename;
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

// TODO: remove it.
void demo_perms(fs::perms p)
{
    std::cout << ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-")
              << ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-")
              << ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-")
              << ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              << std::endl;
}

class OutFileStream : public NonCopyable {
public:
    OutFileStream() = default;
    OutFileStream(const std::filesystem::path& path) { this->set_path(path); }
    ~OutFileStream() { if (this->is_open()) this->close(); }

    void set_path(const std::filesystem::path& path) {
        if (!fs::exists(path) || fs::is_regular_file(path))
            path_ = path;
    }
    const std::filesystem::path& path() const { return path_; }

    bool open(std::ios_base::openmode mode = std::ios::out) { output_.open(path_, mode); }
    bool is_open() const { return output_.is_open(); }
    void close() { if (this->is_open()) output_.close(); }

    OutFileStream& operator<<(std::ostream& (*os)(std::ostream&)) {
        output_ << os;
        return (*this);
    }
    template <typename T>
    OutFileStream& operator<<(const T& data) {
        output_ << data;
        return (*this);
    }

private:
    std::filesystem::path path_;
    std::ofstream output_;
};

}
