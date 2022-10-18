#pragma once

#include "record.hpp"

namespace logger {

namespace fs = std::filesystem;

class IAppender {
public:
    virtual ~IAppender() = default;
    virtual void write(const Record& record) = 0;
};

class FileAppender : public IAppender {
public:
    FileAppender() = default;
    FileAppender(const fs::path& path) { this->set_path(path); }

    void set_path(const fs::path& path) {
        if (!fs::exists(path) || fs::is_regular_file(path))
            path_ = path;
    }
    const fs::path& path() const { return path_; }

    void open(std::ios_base::openmode mode = std::ios::out) { output_.open(path_, mode); }
    bool is_open() const { return output_.is_open(); }
    void close() { if (this->is_open()) output_.close(); }

    FileAppender& operator<<(std::ostream& (*os)(std::ostream&)) {
        output_ << os;
        return (*this);
    }
    template <typename T>
    FileAppender& operator<<(const T& data) {
        output_ << data;
        return (*this);
    }

    void write(const Record& record) override {
        output_ << record.to_string();
    }

private:
    fs::path path_;
    std::ofstream output_;
};

} // logger
