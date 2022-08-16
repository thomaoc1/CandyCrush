#include "swapsLeftDisplay.hpp"


void SwapsLeftDisplay::draw() const {
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, size);
    int width = (Constants::GRIDSIZE - 2) / 4 ; 
    int height = 0;
    fl_measure(text.c_str(), width, height, false);
    fl_draw(text.c_str(), center.x - width / 2, center.y + 40 );
}   
