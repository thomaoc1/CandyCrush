#include "candyDisplay.hpp"

void CandyDisplay::draw(int y, int x) const {
    fl_color(colour);
    fl_begin_polygon();
    fl_circle(Constants::INTER_CELL * y + Constants::GAME_WINDOW_Xi + Constants::INTER_CELL/2, 
                Constants::INTER_CELL * x + Constants::GAME_WINDOW_Yi + Constants::INTER_CELL/2, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}