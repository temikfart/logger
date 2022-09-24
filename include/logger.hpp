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
    Record& ref() { return *this; }

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

class Logger {
public:
    Path path() const { return path_; }

    void set_severity(Severity severity) { severity_ = severity; }
    Severity severity() const { return severity_; }
    static bool check_severity(Severity severity) { return Logger::get()->severity() >= severity; }

    void record(const Record& r) { output_ << r << std::endl; }

    void operator+=(const Record& r) { Logger::get()->record(r); }

    static Logger* init(Severity severity, const Path& path) {
        if (Logger::instance_ == nullptr) {
            Logger::instance_ = new Logger(severity, path);
        }
        return Logger::instance_;
    }
    static Logger* get() {
        if (instance_ == nullptr)
            std::cerr << "Logger: WARNING! Logger is not initialized. Use 'init()' method."
                << std::endl;
        return instance_;
    }

    void delete_instance() {
        this->record(logger::Severity::info, __FILE_NAME__, __FUNCTION__, __LINE__, "End");
        output_.close();
        delete instance_;
    }

    Logger(const Logger& rhs)               = delete;
    Logger(Logger&& rhs)                    = delete;
    Logger& operator=(const Logger& rhs)    = delete;
    Logger& operator=(Logger&& rhs)         = delete;
    ~Logger() {
        this->record(logger::Severity::info, __FILE_NAME__, __FUNCTION__, __LINE__, "End2");
//        output_.close();
    }

private:
    static Logger* instance_;
    Path path_ = std::filesystem::current_path();
    std::fstream output_;
    Severity severity_ = Severity::info;

    Logger(Severity severity, const Path& path) : severity_(severity), path_(path) {
        this->prepare_stream();
        this->record(Severity::info, __FILE_NAME__, __FUNCTION__, __LINE__, "Initial log");
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

Logger* Logger::instance_ = nullptr;

} // logger
