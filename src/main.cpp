#include "logger.hpp"
#include "macro.hpp"

int main() {
    logger::Logger::init(logger::Severity::info, "../log/log.txt");

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
