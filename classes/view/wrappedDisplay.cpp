#include "wrappedDisplay.hpp"

void WrappedDisplay::draw(int row, int col) const {
    fl_color(fl_colour);
    fl_begin_polygon();
    fl_circle(Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2, 
                Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}