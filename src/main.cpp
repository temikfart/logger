#include "macro.hpp"
#include "init.hpp"

int main() {
    logger::init(logger::Severity::info, "../log");
    logger::init(logger::Severity::trace, logger::cout);

//    LOG(logger::info) << "Hello, world!";
//    LOGI << "Short form";

    LOGF << "FATAL ERROR";
    LOGE << "ERROR";
    LOGI << "INFORMATION";
    LOGT << "TRACE";
    LOGD << "DEBUG";

    return 0;
}
