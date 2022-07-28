#ifndef TEXT_DISPLAY_HPP
#define TEXT_DISPLAY_HPP

#include "../../shared/point.hpp"

#include <string>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class TextDisplay {
    Point center;
    std::string text;
    Fl_Font font;
    int size;
public:
    TextDisplay(const Point &center, const std::string &text, Fl_Font font, int size)
        : center{center}, text{text}, font{font}, size{size} {}
    void setSize(int newSize) {size = newSize;}
    void setCenter(const Point &dest) {center = dest;}
    void draw() const;
};

#endif