#pragma once

#include <algorithm>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <fstream>
#include <vector>

#include "appenders.hpp"
#include "record.hpp"
#include "utils.hpp"
#include "severity.hpp"

namespace fs = std::filesystem;

namespace logger {

class Logger : public utils::Singleton<Logger> {
public:
    static Logger* get() {
        auto* instance = Logger::get_instance();
        if (instance == nullptr)
            std::cerr << "Logger: ERROR! Can't print a LOG message: the logger is not initialized. "
                         "Use 'init()' method." << std::endl;
        return instance;
    }
    Logger& add_appender(IAppender* appender) {
        auto apIt = std::find(appenders_.begin(), appenders_.end(), appender);
        if (apIt == appenders_.end()) appenders_.push_back(appender);
        return *this;
    }
    void record(const Record& r) {
        for (auto* ap : appenders_)
            if (ap->severity() >= r.severity())
                ap->write(r);
    }
    void operator+=(const Record& r) { Logger::get()->record(r); }
    ~Logger() = default;

private:
    std::vector<IAppender*> appenders_;
};

} // logger
