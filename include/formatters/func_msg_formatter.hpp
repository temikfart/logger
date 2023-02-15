#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"
#include <sstream>

namespace logger {

class FuncMessagesFormatter {
public:
    FuncMessagesFormatter() : type_(FormatterType::funcMessages) {}
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << r.func << "@" << r.line << ": " << r.msg.str() << std::endl;
        return ss.str();
    }
};

} // logger