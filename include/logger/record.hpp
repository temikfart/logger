#pragma once

#include <sstream>

#include "logger/severity.hpp"
#include "logger/utils.hpp"

namespace logger {

struct Record {
public:
    Record(Severity severity_, const std::string& file_,
           const std::string& func_, unsigned line_)
        : severity(severity_), file(file_), func(func_), line(line_) {}

    std::string to_string() const {
        std::ostringstream ss;
        ss << timestamp.to_string()
           << " [" << utils::to_upper(logger::to_string(severity)) << "]"
           << " " << file
           << " " << func << "()"
           << " at line " << line
           << ": " << utils::rtrim(msg.str())
           << std::endl;
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, const Record& record) {
        os << record.to_string();
        return os;
    }
    template <typename T>
    Record& operator<<(const T& data) {
        msg << data;
        return *this;
    }

    const utils::Time timestamp;
    const Severity severity;
    const std::string file;
    const std::string func;
    const unsigned line;
    std::ostringstream msg;
};

} // logger
