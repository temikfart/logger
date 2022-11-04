#include "log.hpp"

int main() {
    utils::Time::set_timezone(3);
    logger::init(logger::Severity::debug, logger::cout);

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    LOGF << "fatal";
    logger::Logger::get()->set_console_colour(logger::fatal, {"\x1B[0m", "\x1B[0m"});
    LOGF << "fatal";
    LOGW << "warn";

    return 0;
}
