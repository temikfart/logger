#pragma once

#include <iostream>
#include <map>

#include "appenders.hpp"
#include "record.hpp"
#include "severity.hpp"
#include "utils.hpp"

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
        if (appenders_.count(appender->type()) == 0)
            appenders_[appender->type()] = appender;
        return *this;
    }
    void record(const Record& r) {
        for (auto[type, ap]: appenders_)
            if (ap->severity() >= r.severity())
                ap->write(r);
    }
    void set_console_severity(Severity severity) {
        if (appenders_.count(AppenderType::console) > 0)
            appenders_[AppenderType::console]->set_severity(severity);
    }
    void set_file_severity(Severity severity) {
        if (appenders_.count(AppenderType::file) > 0)
            appenders_[AppenderType::file]->set_severity(severity);
    }
    void operator+=(const Record& r) { Logger::get()->record(r); }
    ~Logger() = default;

private:
    std::map<AppenderType, IAppender*> appenders_;
};

} // logger
