#pragma once

#include "logger/formatters/formatters_types.hpp"
#include "logger/record.hpp"

namespace logger {

class TXTFormatter {
public:
    static std::string format(const Record& r) {
        return r.to_string();
    }
    static FormatterType type() { return FormatterType::txt; }
};

} // logger
