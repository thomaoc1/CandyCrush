#include "wallDisplay.hpp"

void WallDisplay::draw(int row, int col) const {
    fl_draw_box(FL_FLAT_BOX, Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, fillColour);
}