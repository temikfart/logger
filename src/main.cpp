#include "macro.hpp"
#include "init.hpp"

int main() {
    logger::init(logger::Severity::debug, "../log");
    logger::init(logger::Severity::info, logger::cout);

//    LOG(logger::info) << "Hello, world!";
//    LOGI << "Short form";

    LOGF << "FATAL ERROR";
    LOGE << "ERROR";
    LOGI << "INFORMATION";
    LOGT << "TRACE";
    LOGD << "DEBUG";

    return 0;
}
