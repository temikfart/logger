#pragma once

#include "colours.hpp"
#include "record.hpp"
#include "severity.hpp"

namespace logger {

namespace fs = std::filesystem;

enum AppenderType {
    file,
    console
};

class IAppender {
public:
    IAppender(AppenderType type) : appender_type_(type) {}
    IAppender(AppenderType type, Severity severity) : appender_type_(type), severity_(severity) {}
    virtual ~IAppender() = default;
    virtual void write(const Record& record) = 0;
    Severity severity() const { return severity_; }
    void set_severity(Severity severity) { severity_ = severity; }
    AppenderType type() const { return appender_type_; }
    virtual void set_colours(Severity severity, const MessageColours& msg_cols) {}
    virtual void turn_colours_on() {}
    virtual void turn_colours_off() {}

private:
    Severity severity_ = silent;
    AppenderType appender_type_;
};

} // logger
