#pragma once

#include "record.hpp"

namespace logger {

class TXTFormatter {
public:
    static std::string format(const Record& r) {
        return r.to_string();
    }
};

} // logger

