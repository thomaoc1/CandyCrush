#include "cellDisplay.hpp"

void CellDisplay::draw() const {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, frameColour);
    if (occupied) occupied->draw(row, col);
}

void CellDisplay::drawNoAnimation() {
    
}