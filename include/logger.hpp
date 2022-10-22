#pragma once

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <fstream>
#include <vector>

#include "appenders.hpp"
#include "record.hpp"
#include "utils.hpp"
#include "severity.hpp"

namespace fs = std::filesystem;

namespace logger {

class Logger : public utils::Singleton<Logger> {
public:
    static Logger& init(Severity severity, StreamType type) {
        static ConsoleAppender console_appender(type);
        return init(severity, &console_appender);
    }
    static Logger& init(Severity severity,
                        const fs::path& path = std::filesystem::current_path()) {
        static FileAppender file_appender(path);
        return init(severity, &file_appender);
    }
    static Logger& init(Severity severity, IAppender* appender = nullptr) {
        static Logger logger(severity);
        return appender ? logger.add_appender(appender) : logger;
    }
    static Logger* get() {
        auto* instance = Logger::get_instance();
        if (instance == nullptr)
            std::cerr << "Logger: ERROR! Can't print a LOG message: the logger is not initialized. "
                         "Use 'init()' method." << std::endl;
        return instance;
    }
    Logger& add_appender(IAppender* appender) {
        auto apIt = std::find(appenders_.begin(), appenders_.end(), appender);
        if (apIt == appenders_.end()) appenders_.push_back(appender);
        return *this;
    }

    void set_severity(Severity severity) { severity_ = severity; }
    Severity severity() const { return severity_; }
    static bool check_severity(Severity severity) {
        return severity <= Logger::get()->severity_;
    }

    void record(const Record& r) {
        for (auto* ap : appenders_)
            ap->write(r);
    }

    void operator+=(const Record& r) { Logger::get()->record(r); }

    ~Logger() = default;

private:
    Severity severity_;
    std::vector<IAppender*> appenders_;

    Logger(Severity severity) : severity_(severity) {}
};

} // logger
