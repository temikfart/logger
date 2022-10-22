#include "logger.hpp"
#include "macro.hpp"

int main() {
    logger::Logger::init(logger::Severity::info, "../log");
    logger::Logger::init(logger::Severity::info, logger::cerr);
    logger::Logger::init(logger::Severity::info, "../logs");

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
