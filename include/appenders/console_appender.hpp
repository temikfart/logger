#pragma once

#include <iostream>
#include <map>
#include <optional>

#include "appenders/appender_interface.hpp"
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

class ConsoleAppender : public IAppender {
public:
    ConsoleAppender(Severity severity, StreamType os_type)
        : IAppender(AppenderType::console, severity),
          output_(os_type == cout ? std::cout : std::cerr) {}

    void write(const Record& record) override {
        Severity sev = record.severity();
        MessageColours msg_col = severity_colours_[sev];
        output_ << to_text_colour(msg_col.text) << to_bg_colour(msg_col.bg);
        output_ << record.to_string();
        output_ << to_text_colour(common);
    }

    void set_msg_colours(Severity severity, const MessageColours& msg_cols) {
        severity_colours_[severity] = msg_cols;
    }
    std::optional<MessageColours> msg_colours(Severity severity) const {
        if (severity == silent)
            return {};
        return std::make_optional(severity_colours_.at(severity));
    }

private:
    std::ostream& output_;
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
