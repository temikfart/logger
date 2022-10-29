#include "log.hpp"

int main() {
    logger::init(logger::Severity::debug, "../log");

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
