#include "broadcastText.hpp"


void BroadcastText::draw() const {
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, size);
    fl_draw(text.c_str(), center.x - 210, center.y);
}