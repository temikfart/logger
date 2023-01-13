#pragma once

#include "record.hpp"

namespace logger {

class JustMessageFormatter {
public:
    static std::string format(const Record& r) {
        return r.msg.str() + "\n";
    }
};

} // logger

