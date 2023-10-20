#pragma once

#include <cctype>
#include <stdexcept>
#include <string_view>

#include "utils.hpp"

namespace logger {

constexpr std::string_view SILENT = "silent";
constexpr std::string_view FATAL = "fatal";
constexpr std::string_view ERROR = "error";
constexpr std::string_view WARN = "warn";
constexpr std::string_view INFO = "info";
constexpr std::string_view DEBUG = "debug";
constexpr std::string_view TRACE = "trace";

enum Severity {
    silent,
    fatal,
    error,
    warn,
    info,
    debug,
    trace,
};

constexpr std::string_view to_string(Severity severity) {
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
