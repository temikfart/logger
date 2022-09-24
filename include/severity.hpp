#pragma once

#include <cctype>

namespace logger {

enum Severity {
    none,
    silent,
    fatal,
    error,
    info,
    trace,
    debug,
};

std::string to_string(const Severity severity) {
    switch (severity) {
        case silent: return "silent";
        case fatal: return "fatal";
        case error: return "error";
        case info: return "info";
        case trace: return "trace";
        case debug: return "debug";
        default: return "none";
    }
}
Severity to_severity(const std::string& severity) {
    switch (tolower(severity[0])) {
        case 's': return Severity::silent;
        case 'f': return Severity::fatal;
        case 'e': return Severity::error;
        case 'i': return Severity::info;
        case 't': return Severity::trace;
        case 'd': return Severity::debug;
        default: return Severity::none;
    }
}

}
