#pragma once

#include <cctype>
#include <stdexcept>

#include "utils.hpp"

namespace logger {

#define SILENT "silent"
#define FATAL "fatal"
#define ERROR "error"
#define WARN "warn"
#define INFO "info"
#define DEBUG "debug"
#define TRACE "trace"

enum Severity {
    silent,
    fatal,
    error,
    warn,
    info,
    debug,
    trace,
};

inline std::string to_string(Severity severity) {
    switch (severity) {
        case silent: return SILENT;
        case fatal: return FATAL;
        case error: return ERROR;
        case warn: return WARN;
        case info: return INFO;
        case debug: return DEBUG;
        case trace: return TRACE;
    }
}
inline Severity to_severity(const std::string& severity_str) {
    std::string severity = utils::to_lower(severity_str);
    if (severity == SILENT) return silent;
    if (severity == FATAL) return fatal;
    if (severity == ERROR) return error;
    if (severity == WARN) return warn;
    if (severity == INFO) return info;
    if (severity == DEBUG) return debug;
    if (severity == TRACE) return trace;
    throw std::invalid_argument("Incorrect representation of severity as string: " + severity_str);
}
inline std::ostream& operator<<(std::ostream& os, Severity severity) {
    os << to_string(severity);
    return os;
}

} // logger
