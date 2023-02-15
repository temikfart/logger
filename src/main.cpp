#include "log.hpp"

int main() {
    logger::init<logger::JSONFormatter>(logger::Severity::info, "../log");
    logger::init(logger::Severity::debug, logger::cout);

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";
    LOGF << "FATAL ERROR";

    logger::Logger::get()->turn_console_colours_off();
    
    LOGE << "ERROR";

    logger::Logger::get()->turn_console_colours_on();

    LOGW << "WARNING";
    LOGT << "TRACE";
    LOGD << "DEBUG";

    return 0;
}
