#include "text.hpp"

void Text::draw() const {
    fl_color(FL_BLACK);
    fl_font(font, size);
    int width = 0, height = 0;
    fl_measure(text.c_str(), width, height, false);
    fl_draw(text.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}