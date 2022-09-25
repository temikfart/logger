#pragma once

#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <fstream>

#include "utils.hpp"
#include "severity.hpp"

namespace logger {

class Logger;
struct Record;

using Path = std::filesystem::path;

struct Record {
public:
    Record(Severity severity, const std::string& file,
           const std::string& func, unsigned line)
        : severity_(severity), file_(file), func_(func), line_(line) {}

    std::string to_string() const {
        std::ostringstream ss;
        ss << utils::to_string(time_)
           << " [" << utils::to_upper(logger::to_string(severity_)) << "]"
           << " " << file_
           << " " << func_ << "()"
           << " at line " << line_
           << ": " << msg_.str();
        return ss.str();
    }

    Severity severity() const { return severity_; }

    friend std::ostream& operator<<(std::ostream& os, const Record& record) {
        os << record.to_string();
        return os;
    }
    template <typename T>
    Record& operator<<(const T& data) {
        msg_ << data;
        return *this;
    }

private:
    const utils::Time time_;
    const Severity severity_;
    const std::string file_;
    const std::string func_;
    const unsigned line_;
    std::ostringstream msg_;
};

class Logger : public utils::Singleton<Logger> {
public:
    Path path() const { return path_; }

    void set_severity(Severity severity) { severity_ = severity; }
    Severity severity() const { return severity_; }
    static bool check_severity(Severity severity) {
        return severity <= Logger::get()->severity_;
    }

    void record(const Record& r) { output_ << r << std::endl; }

    void operator+=(const Record& r) { Logger::get()->record(r); }

    static Logger& init(Severity severity = silent,
                        const Path& path = std::filesystem::current_path()) {
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

private:
    Path path_;
    Severity severity_;
    std::fstream output_;

    Logger(Severity severity, const Path& path) : severity_(severity), path_(path) {
        this->prepare_stream();
    }

    void prepare_stream() {
        output_.open(path_, std::ios::out);
        // TODO: validate file existing.
        // TODO: validate is output opened.
    }
    void record(Severity severity, const std::string& file, const std::string& func,
                unsigned line, const std::string& msg) {
        Record r(severity, file, func, line);
        r << msg;
        this->record(r);
    }
};

} // logger
