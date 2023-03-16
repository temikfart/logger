#include "logger/log.hpp"
#include "logger/initializers/file_appender_initializer.hpp"
#include "logger/initializers/console_appender_initializer.hpp"

int main() {
    logger::init(logger::trace, "../log");

    LOG(logger::fatal) << "lvl in parentheses (fatal)";
    LOG(logger::error) << "lvl in parentheses (error)";
    LOG(logger::warn) << "lvl in parentheses (warn)";
    LOG(logger::info) << "lvl in parentheses (info)";
    LOG(logger::debug) << "lvl in parentheses (debug)";
    LOG(logger::trace) << "lvl in parentheses (trace)";

    LOG_FATAL << "lvl in macro long (fatal)";
    LOG_ERROR << "lvl in macro long (error)";
    LOG_WARN << "lvl in macro long (warn)";
    LOG_INFO << "lvl in macro long (info)";
    LOG_DEBUG << "lvl in macro long (debug)";
    LOG_TRACE << "lvl in macro long (trace)";

    LOGF << "lvl in macro short (fatal)";
    LOGE << "lvl in macro short (error)";
    LOGW << "lvl in macro short (warn)";
    LOGI << "lvl in macro short (info)";
    LOGD << "lvl in macro short (debug)";
    LOGT << "lvl in macro short (trace)";

    LOGF_IF(100 > 0)    << "100 > 0 (true) (fatal)";
    LOGE_IF(1 > 2)      << "1 > 2 (false) (error)";
    LOGW_IF(15 + 7 > 0) << "15 + 7 > 0 (true) (warn)";
    LOGI_IF(0 == 0)     << "0 == 0 (true) (info)";
    LOGD_IF(true)       << "true (true) (debug)";
    LOGT_IF(false)      << "false (false) (trace)";

    logger::Logger::get()->set_severity(logger::error);
    LOGI << "info (lvl=error)";

    logger::Logger::get()->set_severity(logger::info);
    auto severity = logger::Logger::get()->severity(logger::file);
    if (severity.has_value())
        LOGW << "severity level is " << severity.value();

    //////////////////////

    logger::init<logger::FuncMessagesFormatter>(logger::trace, logger::cout);
    LOG(logger::fatal) << "lvl in parentheses (fatal)";
    LOG(logger::error) << "lvl in parentheses (error)";

    logger::Logger::get()->turn_colours_off();

    LOG(logger::warn) << "lvl in parentheses (warn)";
    LOG(logger::info) << "lvl in parentheses (info)";
    LOG(logger::debug) << "lvl in parentheses (debug)";

    logger::Logger::get()->turn_colours_on();

    LOG(logger::trace) << "lvl in parentheses (trace)";

    logger::init<logger::JSONFormatter>(logger::warn, logger::cout);
    LOGI << "json, hello";

    // TODO: add another tests.

    return 0;
}
