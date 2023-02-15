#pragma once

#include <iostream>
#include <map>

#include "appenders/appender_interface.hpp"
#include "formatters/formatter_interface.hpp"
#include "colours.hpp"
#include "record.hpp"
#include "severity.hpp"

namespace logger {

enum StreamType {
    cout,
    cerr
};

struct MessageColours {
    MessageColours() = default;
    MessageColours(Colour text_col, Colour bg_col)
        : text(text_col), bg(bg_col) {}

    Colour text = common;
    Colour bg = common;
};

template<class Formatter>
class ConsoleAppender : public IAppender {
public:
    ConsoleAppender(Severity severity, StreamType os_type)
        : IAppender(AppenderType::console, severity),
          output_(os_type == cout ? std::cout : std::cerr) {}
    void write(const Record& record) override {
        // TODO: come up how to make JSON array, if JSONFormatter is used as template.
        Severity sev = record.severity;
        MessageColours msg_col = severity_colours_[sev];
        if (coloured)
            output_ << to_text_colour(msg_col.text) << to_bg_colour(msg_col.bg);
        output_ << Formatter::format(record);
        output_ << to_text_colour(common);
    }
    void set_msg_colours(Severity severity, const MessageColours& msg_cols) {
        severity_colours_[severity] = msg_cols;
    }
    void turn_colours_on() { coloured = true; }
    void turn_colours_off() { coloured = false; }
    FormatterType formatter_type() const { return Formatter::type(); }

private:
    std::ostream& output_;
    bool coloured = true;
    std::map<Severity, MessageColours> severity_colours_ = {
        {fatal, {white, red}},
        {error, {red, common}},
        {warning, {yellow, common}},
        {info, {common, common}},
        {trace, {light_gray, common}},
        {debug, {white, common}}
    };
};

} // logger
