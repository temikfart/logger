#pragma once

#include "formatters_types.hpp"
#include "record.hpp"
#include <sstream>

namespace logger {

class FuncMessagesFormatter {
public:
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << r.func << "@" << r.line << ": " << r.msg.str() << std::endl;
        return ss.str();
    }
    static FormatterType type() { return FormatterType::funcMessages; }
};

} // logger