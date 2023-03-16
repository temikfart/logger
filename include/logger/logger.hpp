#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <iostream>
#include <map>
#include <optional>

#include "logger/appenders/appender_interface.hpp"
//#include "logger/appenders/console_appender.hpp"
//#include "logger/appenders/file_appender.hpp"
//#include "logger/record.hpp"
//#include "logger/severity.hpp"
#include "logger/utils.hpp"

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
    void write(const Record& r) {
        for (auto[type, ap]: appenders_)
            if (ap->severity() >= r.severity)
                ap->write(r);
    }

    void set_severity(Severity severity) {
        for (auto[type, ap]: appenders_)
            ap->set_severity(severity);
    }
    void set_severity(Severity severity, AppenderType type) {
        if (appenders_.count(type) > 0)
            appenders_.at(type)->set_severity(severity);
    }
    std::optional<Severity> severity(AppenderType type) {
        if (appenders_.count(type) > 0)
            return appenders_.at(type)->severity();
        return {};
    }

    void change_colours(Severity severity, const MessageColours& msg_cols) {
        if (appenders_.count(AppenderType::console) > 0)
            appenders_.at(AppenderType::console)->set_colours(severity, msg_cols);
    }
    void turn_colours_on() {
        if (appenders_.count(AppenderType::console) > 0)
            appenders_.at(AppenderType::console)->turn_colours_on();
    }
    void turn_colours_off() {
        if (appenders_.count(AppenderType::console) > 0)
            appenders_.at(AppenderType::console)->turn_colours_off();
    }
//    static void set_timezone(int tz)  {
//        utils::Time::set_timezone(tz);
//    }

    void operator+=(const Record& r) { Logger::get()->write(r); }
    ~Logger() = default;

private:
    std::map<AppenderType, IAppender*> appenders_;
};

} // logger

#endif // LOGGER_HPP_
