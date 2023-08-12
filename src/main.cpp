#include "logger/log.hpp"
#include "logger/initializers/file_appender_initializer.hpp"

int main() {
    logger::init(logger::Severity::info, "../log");

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
