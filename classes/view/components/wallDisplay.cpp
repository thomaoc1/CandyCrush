#include "wallDisplay.hpp"

void WallDisplay::drawShape() const {
    fl_draw_box(FL_FLAT_BOX, 
                static_cast<int>(getCenter().x - Constants::INTER_CELL/2),
                static_cast<int>(getCenter().y - Constants::INTER_CELL/2), 
                size,
                size, 
                fillColour);
}