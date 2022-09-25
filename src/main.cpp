#include "logger.hpp"
#include "macro.hpp"

#include <filesystem>

int main() {
    std::filesystem::path p = std::filesystem::canonical("../log/log.txt");

    auto& logger = logger::Logger::init(logger::Severity::info, p);

    LOG(logger::info) << "Hello, world!";
    LOGI << "Short form";

    return 0;
}
