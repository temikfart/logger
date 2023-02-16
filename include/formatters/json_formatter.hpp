#pragma once

#include "formatter_interface.hpp"
#include "record.hpp"
#include <sstream>

namespace logger {

class JSONFormatter : public IFormatter {
public:
    JSONFormatter() : IFormatter(FormatterType::json) {}
    static std::string format(const Record& r) {
        std::ostringstream ss;
        ss << "{"
           << R"("timestamp":")" << r.timestamp.to_string(true) << "\","
           << R"("severity":")" << utils::to_upper(logger::to_string(r.severity)) << "\","
           << R"("file":")" << r.file << "\","
           << R"("function":")" << r.func << "\","
           << R"("line":")" << r.line << "\","
           << R"("message":")" << utils::remove_linebreaks(r.msg.str()) << "\""
           << "}" << std::endl;
        return ss.str();
    }
};

} // logger