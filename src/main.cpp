#include "log.hpp"

int main() {
    logger::init(logger::Severity::info, "../log");

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
