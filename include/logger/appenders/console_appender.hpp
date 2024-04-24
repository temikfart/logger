#pragma once

#include <iostream>
#include <map>

#include "logger/appenders/appender_interface.hpp"
#include "logger/colours.hpp"
#include "logger/formatters/formatters_types.hpp"
#include "logger/record.hpp"
#include "logger/severity.hpp"

namespace logger {

enum StreamType {
    cout,
    cerr
};

template<class Formatter>
class ConsoleAppender : public IAppender {
public:
    ConsoleAppender(Severity severity, StreamType os_type)
        : IAppender(AppenderType::console, severity),
          output_(os_type == cout ? std::cout : std::cerr) {}
    void write(const Record& record) override {
        static bool is_first_record = true;
        if (Formatter::type() == FormatterType::json) {
            if (is_first_record) {
                is_first_record = false;
                output_ << "[\n";
            } else {
                output_ << ",\n";
            }
            output_.flush();
        }

        Severity sev = record.severity;
        MessageColours msg_col = severity_colours_[sev];
        if (coloured)
            output_ << to_text_colour(msg_col.text) << to_bg_colour(msg_col.bg);
        output_ << Formatter::format(record);
        output_ << to_text_colour(common) << to_bg_colour(common) << std::flush;
    }
    void set_colours(Severity severity, const MessageColours& msg_cols) override {
        severity_colours_[severity] = msg_cols;
    }
    void turn_colours_on() override { coloured = true; }
    void turn_colours_off() override { coloured = false; }
    ~ConsoleAppender() {
        if (Formatter::type() == FormatterType::json)
            output_ << "\n]" << std::endl << std::flush;
    }

private:
    std::ostream& output_;
    bool coloured = true;
    std::map<Severity, MessageColours> severity_colours_ = {
        {fatal, {white, red}},
        {error, {red, common}},
        {warn, {yellow, common}},
        {info, {common, common}},
        {trace, {light_gray, common}},
        {debug, {white, common}}
    };
};

} // logger
