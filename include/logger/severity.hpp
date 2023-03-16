#pragma once

#include <cctype>

namespace logger {

enum Severity {
    silent,
    fatal,
    error,
    warn,
    info,
    debug,
    trace,
};

inline std::string to_string(const Severity severity) {
    switch (severity) {
        case fatal: return "fatal";
        case error: return "error";
        case warn: return "warning";
        case info: return "info";
        case trace: return "trace";
        case debug: return "debug";
        default: return "silent";
    }
}
inline Severity to_severity(const std::string& severity) {
    switch (tolower(severity[0])) {
        case 'f': return Severity::fatal;
        case 'e': return Severity::error;
        case 'w': return Severity::warn;
        case 'i': return Severity::info;
        case 't': return Severity::trace;
        case 'd': return Severity::debug;
        default: return Severity::silent;
    }
}

inline std::ostream& operator<<(std::ostream& os, Severity severity) {
    os << to_string(severity);
    return os;
}

} // logger
