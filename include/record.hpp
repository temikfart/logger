#pragma once

#include <sstream>

#include "severity.hpp"
#include "utils.hpp"

namespace logger {

struct Record {
public:
    Record(Severity severity, const std::string& file,
           const std::string& func, unsigned line)
        : severity_(severity), file_(file), func_(func), line_(line) {}

    std::string to_string() const {
        std::ostringstream ss;
        ss << time_.to_string()
           << " [" << utils::to_upper(logger::to_string(severity_)) << "]"
           << " " << file_
           << " " << func_ << "()"
           << " at line " << line_
           << ": " << utils::remove_linebreaks(msg_.str())
           << std::endl;
        return ss.str();
    }

    Severity severity() const { return severity_; }

    friend std::ostream& operator<<(std::ostream& os, const Record& record) {
        os << record.to_string();
        return os;
    }
    template <typename T>
    Record& operator<<(const T& data) {
        msg_ << data;
        return *this;
    }

private:
    const utils::Time time_;
    const Severity severity_;
    const std::string file_;
    const std::string func_;
    const unsigned line_;
    std::ostringstream msg_;
};

} // logger
