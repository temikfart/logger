#pragma once

#include "logger/appenders/console_appender.hpp"
#include "logger/formatters/func_msg_formatter.hpp"
#include "logger/formatters/json_formatter.hpp"
#include "logger/formatters/only_msg_formatter.hpp"
#include "logger/formatters/text_formatter.hpp"
#include "logger/logger.hpp"
#include "logger/severity.hpp"
#include "logger/init.hpp"

namespace logger {

template<class Formatter>
Logger& init(Severity severity, StreamType type) {
    static ConsoleAppender<Formatter> console_appender(severity, type);
    return init(&console_appender);
}
Logger& init(Severity severity, StreamType type) {
    return init<TXTFormatter>(severity, type);
}

} // logger
