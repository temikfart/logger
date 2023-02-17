#pragma once

#include "formatters_types.hpp"
#include "record.hpp"

namespace logger {

class OnlyMessagesFormatter {
public:
    static std::string format(const Record& r) {
        return r.msg.str() + "\n";
    }
    static FormatterType type() { return FormatterType::onlyMessages; }
};

} // logger
