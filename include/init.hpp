#pragma once

#include "logger.hpp"

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
                    const fs::path& path = std::filesystem::current_path()) {
    static FileAppender file_appender(severity, path);
    return init(&file_appender);
}

} // logger
