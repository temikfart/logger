#include "logger/log.hpp"
#include "logger/initializers/file_appender_initializer.hpp"
#include "logger/initializers/console_appender_initializer.hpp"
#include "logger/formatters/only_msg_formatter.hpp"
#include "handler.hpp"

int main() {
//    logger::init<logger::JSONFormatter>(logger::Severity::trace, "../log");
    logger::init<logger::FuncMessagesFormatter>(logger::Severity::debug, logger::StreamType::cout);
    logger::Logger::get()->turn_colours_off();

    LOGD << "We want to read x value.";
    logger::Logger::get()->turn_colours_on();
    int x;
    std::cin >> x;
    LOGE_IF(x <= 0) << "Variable x is too small!!!1";


    handler(x);

    LOGT << "End.";
    return 0;
}
