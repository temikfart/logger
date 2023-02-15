#pragma once

namespace logger {

enum FormatterType {
	funcMessages,
	JSON,
	onlyMessages,
	TXT,
}

class IFormatter {
public:
	IFormatter(FormatterType t) : type(t) {}
	virtual static std::string format(const Record& r) = 0;
	static FormatterType type() const { return type_; }

private:
	FormatterType type_;
}

} // logger