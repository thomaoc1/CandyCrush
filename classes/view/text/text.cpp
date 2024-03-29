#include "text.hpp"


/**
 * @brief Displays text
 * 
 */
void Text::draw() const {
    fl_color(FL_BLACK);
    fl_font(font, size);
    int width = 0, height = 0;
    fl_measure(text.c_str(), width, height, false);
    fl_draw(text.c_str(), center.x-width/2, center.y-fl_descent()+height/2);
}


/**
 * @brief Displays text given an offest
 * 
 * @param xOffset 
 * @param yOffset 
 */
void Text::draw(int xOffset, int yOffset) const {
    fl_color(FL_BLACK);
    fl_font(font, size);
    int width = 0, height = 0;
    fl_measure(text.c_str(), width, height, false);
    fl_draw(text.c_str(), center.x - width / 2 + xOffset, center.y + yOffset);
}