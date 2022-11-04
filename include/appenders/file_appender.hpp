#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>

#include "appenders/appenders.hpp"
#include "record.hpp"
#include "severity.hpp"
#include "utils.hpp"

namespace logger {

namespace fs = std::filesystem;

class FileAppender : public IAppender {
public:
    FileAppender() : IAppender(AppenderType::file) {}
    FileAppender(Severity severity, const fs::path& path,
                 std::ios_base::openmode mode = std::ios::out)
        : IAppender(AppenderType::file, severity) {
        if (utils::maybe_regular_file(path) && fs::exists(utils::get_parent_path(path))) {
            this->set_path(path);
        } else {
            this->create_dir(path);
            this->configure_file();
        }
        this->open(mode);
    }

    void set_path(const fs::path& path) {
        if (!fs::exists(path) || fs::is_regular_file(path))
            path_ = path;
    }
    const fs::path& path() const { return path_; }

    void open(std::ios_base::openmode mode = std::ios::out) { output_.open(path_, mode); }
    void close() { if (this->is_open()) output_.close(); }
    bool is_open() const { return output_.is_open(); }

    template <typename T>
    FileAppender& operator<<(const T& data) {
        output_ << data;
        return (*this);
    }
    FileAppender& operator<<(std::ostream& (* os)(std::ostream&)) {
        output_ << os;
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
    void configure_file() {
        utils::Time timestamp;
        auto filepath = utils::to_filepath(timestamp, dir_);
        this->set_path(filepath);
    }
};

} // logger
