#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"
#include <sstream>

namespace logger {

class JSONFormatter {
public:
    JSONFormatter() : type_(FormatterType::JSON) {}
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << "{"
           << "\"timestamp\":\"" << r.timestamp.to_string(true) << "\","
           << "\"severity\":\"" << utils::to_upper(logger::to_string(r.severity)) << "\","
           << "\"file\":\"" << r.file << "\","
           << "\"function\":\"" << r.func << "\","
           << "\"line\":\"" << r.line << "\","
           << "\"message\":\"" << utils::remove_linebreaks(r.msg.str()) << "\""
           << "}" << std::endl;
        return ss.str();
    }
};

} // logger