#include "scoreDisplay.hpp"


void ScoreDisplay::draw() const {
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, size);
    int width, height;
    fl_measure(text.c_str(), width, height, false);
    fl_draw(text.c_str(), center.x - width / 2, center.y + 2 * height);
}