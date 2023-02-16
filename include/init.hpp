#pragma once

#include <filesystem>

#include "appenders/appender_interface.hpp"
#include "formatters/func_msg_formatter.hpp"
#include "formatters/json_formatter.hpp"
#include "formatters/only_msg_formatter.hpp"
#include "formatters/text_formatter.hpp"
#include "logger.hpp"
#include "severity.hpp"

namespace fs = std::filesystem;

namespace logger {

Logger& init(IAppender* appender = nullptr) {
    static Logger logger;
    return appender ? logger.add_appender(appender) : logger;
}

template<class Formatter>
Logger& init(Severity severity, StreamType type) {
    static ConsoleAppender<Formatter> console_appender(severity, type);
    return init(&console_appender);
}
Logger& init(Severity severity, StreamType type) {
    return init<TXTFormatter>(severity, type);
}

template<class Formatter>
Logger& init(Severity severity,
             const fs::path& path = fs::current_path(),
             std::ios_base::openmode mode = std::ios::out) {
    static FileAppender<Formatter> file_appender(severity, path, mode);
    return init(&file_appender);
}
Logger& init(Severity severity,
             const fs::path& path = fs::current_path(),
             std::ios_base::openmode mode = std::ios::out) {
    return init<TXTFormatter>(severity, path, mode);
}

} // logger
