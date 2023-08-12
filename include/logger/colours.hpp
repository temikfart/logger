#pragma once

namespace logger {

enum Colour {
    common,
    white,
    light_gray,
    gray,
    yellow,
    red
};

struct MessageColours {
    MessageColours() = default;
    MessageColours(Colour text_col, Colour bg_col)
        : text(text_col), bg(bg_col) {}

    Colour text = common;
    Colour bg = common;
};

inline std::string to_text_colour(Colour col) {
    switch (col) {
        case white: return "\x1B[97m";
        case light_gray: return "\x1B[96m";
        case gray: return "\x1B[0m";
        case yellow: return "\x1B[93m";
        case red: return "\x1B[91m";
        default: return "\x1B[0m";
    }
}

inline std::string to_bg_colour(Colour col) {
    switch (col) {
        case red: return "\x1B[41m";
        default: return "\x1B[0K";
    }
}

} // logger
