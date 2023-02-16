#pragma once

#include "record.hpp"

namespace logger {

enum FormatterType {
	funcMessages,
	json,
	onlyMessages,
	txt,
};

class IFormatter {
public:
	IFormatter(FormatterType t) : type_(t) {}
	static std::string format(const Record& r);
	FormatterType type() const { return type_; }

protected:
	FormatterType type_;
};

} // logger