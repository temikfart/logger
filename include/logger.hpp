#pragma once

#include <iostream>
#include <map>
#include <optional>

#include "appenders/appender_interface.hpp"
#include "appenders/console_appender.hpp"
#include "appenders/file_appender.hpp"
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

//    template<class Formatter>
//    void set_console_colour(Severity severity, const MessageColours& msg_cols) {
//        if (appenders_.count(AppenderType::console) > 0) {
//            ConsoleAppender<Formatter>* cons_ap
//                = dynamic_cast<ConsoleAppender<Formatter>*>(appenders_[AppenderType::console]);
//            cons_ap->set_msg_colours(severity, msg_cols);
//        }
//    }
//    template<class Formatter>
//    void turn_console_colours_on() {
//        if (appenders_.count(AppenderType::console) > 0) {
//            ConsoleAppender<Formatter>* cons_ap
//                = dynamic_cast<ConsoleAppender<Formatter>*>(appenders_[AppenderType::console]);
//            cons_ap->turn_colours_on();
//        }
//    }
//    template<class Formatter>
//    void turn_console_colours_off() {
//        if (appenders_.count(AppenderType::console) > 0) {
//            ConsoleAppender<Formatter>* cons_ap
//                = dynamic_cast<ConsoleAppender<Formatter>*>(appenders_[AppenderType::console]);
//            cons_ap->turn_colours_off();
//        }
//    }

    void operator+=(const Record& r) { Logger::get()->write(r); }
    ~Logger() = default;

private:
    std::map<AppenderType, IAppender*> appenders_;
};

} // logger
