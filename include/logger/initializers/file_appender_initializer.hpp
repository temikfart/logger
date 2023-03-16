#pragma once

#include "logger/appenders/file_appender.hpp"
#include "logger/formatters/func_msg_formatter.hpp"
#include "logger/formatters/json_formatter.hpp"
#include "logger/formatters/only_msg_formatter.hpp"
#include "logger/formatters/text_formatter.hpp"
#include "logger/logger.hpp"
#include "logger/severity.hpp"
#include "logger/init.hpp"

namespace logger {

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
