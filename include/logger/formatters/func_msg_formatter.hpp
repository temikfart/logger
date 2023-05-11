#pragma once

#include <sstream>

#include "logger/formatters/formatters_types.hpp"
#include "logger/record.hpp"

namespace logger {

class FuncMessagesFormatter {
public:
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << r.func << "@" << r.line << ": " << r.msg.str() << std::endl;
        return ss.str();
    }
    inline static FormatterType type() { return FormatterType::funcMessages; }
};

} // logger
