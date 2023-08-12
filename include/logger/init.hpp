#pragma once

#include <filesystem>

#include "logger/appenders/appender_interface.hpp"
#include "logger/logger.hpp"

namespace fs = std::filesystem;

namespace logger {

Logger& init(IAppender* appender = nullptr) {
    static Logger logger;
    return appender ? logger.add_appender(appender) : logger;
}

} // logger
