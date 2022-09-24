#include "logger.hpp"
#include "macro.hpp"

#include <filesystem>

class Test {
public:
    Test* init() {
        if (instance_ == nullptr)
            instance_ = new Test();
        return instance_;
    }
    ~Test() { std::cout << "deleted\n"; }
    Test() { std::cout << "created\n"; }

private:
    Test* instance_ = nullptr;
};

int main() {
    std::filesystem::path p = std::filesystem::canonical("../log/log.txt");

    auto* logger = logger::Logger::init(logger::Severity::info, p);
    std::cout << logger::to_string(logger->severity()) << " " << logger->path() << std::endl;
//    logger::Logger::get()->record(logger::info, GET_FILE, GET_FUNC, GET_LINE, "Hello, world!");

//    LOG(logger::info) << "Hello, world!";

//    logger::Record r(logger::info, GET_FILE, GET_FUNC, GET_LINE);
//    r << "hello";
//    *logger::Logger::get() += r;

//    auto* logger2 = logger::Logger::init(logger::Severity::debug, p.parent_path());
//    std::cout << logger::to_string(logger2->severity()) << " " << logger2->path() << std::endl;
//    logger::Logger::get()->record(logger::fatal, GET_FILE, GET_FUNC, GET_LINE, "Fatal error!");

//    std::cout << (logger == logger2) << std::endl;

//    LOG(logger::info) << "Hello, world!";
//    LOG(logger::fatal) << "fatal error!";

//    logger::Logger::get()->delete_instance();

//    delete logger::Logger::instance_;
//
//    Test test;
//    Test* test2 = test.init();
//    delete test2;
//
//    std::cout << "main end" << std::endl;

    int* a = (int*)malloc(50);

    return 0;
}
