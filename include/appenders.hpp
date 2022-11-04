#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <optional>

#include "record.hpp"
#include "severity.hpp"
#include "utils.hpp"
#include "colours.hpp"

namespace logger {

namespace fs = std::filesystem;

enum StreamType {
    cout,
    cerr
};

enum AppenderType {
    file,
    console
};

class IAppender {
public:
    IAppender(AppenderType type) : appender_type_(type) {}
    IAppender(AppenderType type, Severity severity) : appender_type_(type), severity_(severity) {}
    virtual ~IAppender() = default;
    virtual void write(const Record& record) = 0;
    Severity severity() const { return severity_; }
    void set_severity(Severity severity) { severity_ = severity; }
    AppenderType type() const { return appender_type_; }

private:
    Severity severity_ = silent;
    AppenderType appender_type_;
};

class FileAppender : public IAppender {
public:
    FileAppender() : IAppender(AppenderType::file) {}
    FileAppender(Severity severity, const fs::path& path,
                 std::ios_base::openmode mode = std::ios::out)
        : IAppender(AppenderType::file, severity) {
        if (utils::maybe_regular_file(path) && fs::exists(utils::get_parent_path(path))) {
            this->set_path(path);
        } else {
            this->create_dir(path);
            this->configure_file();
        }
        this->open(mode);
    }

    void set_path(const fs::path& path) {
        if (!fs::exists(path) || fs::is_regular_file(path))
            path_ = path;
    }
    const fs::path& path() const { return path_; }

    void open(std::ios_base::openmode mode = std::ios::out) { output_.open(path_, mode); }
    bool is_open() const { return output_.is_open(); }
    void close() { if (this->is_open()) output_.close(); }

    FileAppender& operator<<(std::ostream& (*os)(std::ostream&)) {
        output_ << os;
        return (*this);
    }
    template <typename T>
    FileAppender& operator<<(const T& data) {
        output_ << data;
        return (*this);
    }

    void write(const Record& record) override {
        output_ << record.to_string();
    }

private:
    fs::path dir_;
    fs::path path_;
    std::ofstream output_;

    void create_dir(const fs::path& path) {
        if (fs::exists(path))
            dir_ = (fs::is_directory(path) ? path : path.parent_path()).string();
        else
            dir_ = utils::get_parent_path(path).string() + "/" + utils::get_dirname(path);
        fs::create_directories(dir_);
    }
    void configure_file() {
        utils::Time timestamp;
        auto filepath = utils::to_filepath(timestamp, dir_);
        this->set_path(filepath);
    }
};

struct MessageColours {
    MessageColours() {};
    MessageColours(Colour text_col, Colour bg_col)
    : text(text_col), bg(bg_col) {}

    Colour text = common;
    Colour bg = common;
};

class ConsoleAppender : public IAppender {
public:
    ConsoleAppender(Severity severity, StreamType os_type)
        : IAppender(AppenderType::console, severity),
          output_(os_type == cout ? std::cout : std::cerr) {}

    void write(const Record& record) override {
        Severity sev = record.severity();
        MessageColours msg_col = severity_colours_[sev];
        output_ << to_text_colour(msg_col.text) << to_bg_colour(msg_col.bg);
        output_ << record.to_string();
        output_ << to_text_colour(common);
    }

    void set_msg_colours(Severity severity, const MessageColours& msg_cols) {
        severity_colours_[severity] = msg_cols;
    }
    std::optional<MessageColours> msg_colours(Severity severity) const {
        if (severity == silent)
            return {};
        return std::make_optional(severity_colours_.at(severity));
    }

private:
    std::ostream& output_;
    std::map<Severity, MessageColours> severity_colours_ = {
        {fatal, {white, red}},
        {error, {red, common}},
        {warning, {yellow, common}},
        {info, {common, common}},
        {trace, {light_gray, common}},
        {debug, {white, common}}
    };
};

} // logger
