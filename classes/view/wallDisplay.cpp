#include "wallDisplay.hpp"

void WallDisplay::draw(int y, int x) const {
    fl_draw_box(FL_FLAT_BOX, Constants::INTER_CELL * y + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * x + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, fillColour);
}