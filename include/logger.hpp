#pragma once

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <fstream>

#include "appenders.hpp"
#include "record.hpp"
#include "utils.hpp"
#include "severity.hpp"

namespace fs = std::filesystem;

namespace logger {

class Logger : public utils::Singleton<Logger> {
public:
    static Logger& init(Severity severity = silent,
                        const fs::path& path = std::filesystem::current_path()) {
        static Logger logger(severity, path);
        return logger;
    }
    static Logger* get() {
        auto* instance = Logger::get_instance();
        if (instance == nullptr)
            std::cerr << "Logger: ERROR! Can't print a LOG message: the logger is not initialized. "
                         "Use 'init()' method." << std::endl;
        return instance;
    }

    void set_severity(Severity severity) { severity_ = severity; }
    Severity severity() const { return severity_; }
    static bool check_severity(Severity severity) {
        return severity <= Logger::get()->severity_;
    }

    void record(const Record& r) { output_ << r << std::endl; }

    void operator+=(const Record& r) { Logger::get()->record(r); }

    ~Logger() = default;

private:
    fs::path log_dir_path_;
    Severity severity_;
    FileAppender output_;

    Logger(Severity severity, const fs::path& log_dir_path) : severity_(severity) {
        this->create_log_dir(log_dir_path);
        this->open_log_file();
    }

    void create_log_dir(const fs::path& path) {
        if (fs::exists(path))
            log_dir_path_
                = (fs::is_directory(path) ? path : path.parent_path()).string();
        else
            log_dir_path_
                = utils::get_parent_path(path).string() + "/" + utils::get_dirname(path);
        fs::create_directories(log_dir_path_);
    }
    void open_log_file() {
        utils::Time timestamp;
        auto filepath = utils::to_filepath(timestamp, log_dir_path_);
        output_.set_path(filepath);
        output_.open();
    }
};

} // logger
