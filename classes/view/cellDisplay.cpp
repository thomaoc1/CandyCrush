#include "cellDisplay.hpp"

void CellDisplay::drawShape() const {
    fl_draw_box(FL_BORDER_FRAME, 
                static_cast<int>(getCenter().x/* - Constants::INTER_CELL/2*/),
                static_cast<int>(getCenter().y/* - Constants::INTER_CELL/2*/), 
                size,
                size, 
                frameColour);
}
