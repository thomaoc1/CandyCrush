#include "cellDisplay.hpp"

void CellDisplay::draw(int row, int col) const {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, frameColour);
    if (occupied) occupied->draw(row, col);
}