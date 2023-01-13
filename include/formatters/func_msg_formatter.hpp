#pragma once

#include "record.hpp"
#include <sstream>

namespace logger {

class FuncMessageFormatter {
public:
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << r.func << "@" << r.line << ": " << r.msg.str() << std::endl;
        return ss.str();
    }
};

} // logger