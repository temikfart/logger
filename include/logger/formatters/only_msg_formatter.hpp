#pragma once

#include "logger/formatters/formatters_types.hpp"
#include "logger/record.hpp"

namespace logger {

class OnlyMessagesFormatter {
public:
    static std::string format(const Record& r) {
        return r.msg.str() + "\n";
    }
    static FormatterType type() { return FormatterType::onlyMessages; }
};

} // logger
