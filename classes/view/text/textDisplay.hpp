#ifndef TEXT_DISPLAY_HPP
#define TEXT_DISPLAY_HPP

#include "text.hpp"

class TextDisplay : public Text {
public:
    TextDisplay (const Point &center, const std::string &text, Fl_Font font, int size) 
        : Text{center, text, font, size} {}
    TextDisplay() = default;
    TextDisplay(const TextDisplay &) = default;
    TextDisplay(TextDisplay &&) = default;

    void draw() const override;
};

#endif