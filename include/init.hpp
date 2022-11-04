#pragma once

#include <filesystem>

#include "appenders.hpp"
#include "logger.hpp"
#include "severity.hpp"

namespace fs = std::filesystem;

namespace logger {

Logger& init(IAppender* appender = nullptr) {
    static Logger logger;
    return appender ? logger.add_appender(appender) : logger;
}

Logger& init(Severity severity, StreamType type) {
    static ConsoleAppender console_appender(severity, type);
    return init(&console_appender);
}
Logger& init(Severity severity,
             const fs::path& path = std::filesystem::current_path(),
             std::ios_base::openmode mode = std::ios::out) {
    static FileAppender file_appender(severity, path, mode);
    return init(&file_appender);
}

} // logger
