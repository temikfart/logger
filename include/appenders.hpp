#pragma once

#include "record.hpp"

namespace logger {

namespace fs = std::filesystem;

enum StreamType {
    cout,
    cerr
};

class IAppender {
public:
    virtual ~IAppender() = default;
    virtual void write(const Record& record) = 0;
};

class FileAppender : public IAppender {
public:
    FileAppender() = default;
    FileAppender(const fs::path& path) {
        this->create_dir(path);
        this->open_file();
    }

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
    fs::path dir_;
    fs::path path_;
    std::ofstream output_;

    void create_dir(const fs::path& path) {
        if (fs::exists(path))
            dir_ = (fs::is_directory(path) ? path : path.parent_path()).string();
        else
            dir_ = utils::get_parent_path(path).string() + "/" + utils::get_dirname(path);
        fs::create_directories(dir_);
    }
    void open_file() {
        utils::Time timestamp;
        auto filepath = utils::to_filepath(timestamp, dir_);
        this->set_path(filepath);
        this->open();
    }
};

class ConsoleAppender : public IAppender {
public:
    ConsoleAppender(StreamType type) : output_(type == cout ? std::cout : std::cerr) {}

    void write(const Record& record) override {
        output_ << record.to_string();
    }

private:
    std::ostream& output_;
};

} // logger
