#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"

namespace logger {

class TXTFormatter : public IFormatter {
public:
    TXTFormatter() : IFormatter(FormatterType::txt) {}
    static std::string format(const Record& r) {
        return r.to_string();
    }
};

} // logger

