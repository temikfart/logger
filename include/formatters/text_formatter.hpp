#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"

namespace logger {

class TXTFormatter : IFormatter {
public:
    TXTFormatter() : type_(FormatterType::TXT) {}
    static std::string format(const Record& r) {
        return r.to_string();
    }
};

} // logger

