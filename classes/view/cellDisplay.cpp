#include "cellDisplay.hpp"

void CellDisplay::draw() {
    fl_draw_box(FL_BORDER_FRAME, 
                static_cast<int>(getCenter().x/* - Constants::INTER_CELL/2*/),
                static_cast<int>(getCenter().y/* - Constants::INTER_CELL/2*/), 
                Constants::INTER_CELL,
                Constants::INTER_CELL, 
                frameColour);
}
