#pragma once

#include "formatters_types.hpp"
#include "record.hpp"
#include <sstream>

namespace logger {

class JSONFormatter {
public:
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << "\t{\n"
           << "\t\t" << R"("timestamp":")" << r.timestamp.to_string(true) << "\",\n"
           << "\t\t" << R"("severity":")" << utils::to_upper(logger::to_string(r.severity)) << "\",\n"
           << "\t\t" << R"("file":")" << r.file << "\",\n"
           << "\t\t" << R"("function":")" << r.func << "\",\n"
           << "\t\t" << R"("line":")" << r.line << "\",\n"
           << "\t\t" << R"("message":")" << utils::remove_linebreaks(r.msg.str()) << "\"\n"
           << "\t}";
        return ss.str();
    }
    static FormatterType type() { return FormatterType::json; }
};

} // logger
