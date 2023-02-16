#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"

namespace logger {

class OnlyMessagesFormatter : public IFormatter {
public:
    OnlyMessagesFormatter() : IFormatter(FormatterType::onlyMessages) {}
    static std::string format(const Record& r) {
        return r.msg.str() + "\n";
    }
};

} // logger

