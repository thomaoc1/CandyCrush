#include "constants.hpp"

const std::string Constants::BAD_SWAP = "Can't swap those, try again.";
const std::string Constants::GAME_WON = "You won !";
const std::string Constants::GAME_LOST = "GameOver, you lost !";
const std::string Constants::SHUFFLING = "No possible moves, shuffling";

const double Constants::FPS = 60;
const double Constants::WINDOW_HEIGHT = 750;
const double Constants::WINDOW_WIDTH = 750;
const double Constants::GAME_WINDOW_Xi = Constants::WINDOW_WIDTH /2 - Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Xf = Constants::WINDOW_WIDTH /2 + Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Yi = ((Constants::WINDOW_HEIGHT * 3) / 5) - Constants::HALVE_GRIDSIZE;
const double Constants::GAME_WINDOW_Yf = ((Constants::WINDOW_HEIGHT * 3) / 5) + Constants::HALVE_GRIDSIZE;
const double Constants::CELL_SIZE = 50;

const double Constants::HALVE_CELL_SIZE = 25;
const double Constants::GAP_SIZE = 4;
const double Constants::STEP_SIZE = ( Constants::HALVE_CELL_SIZE + Constants::GAP_SIZE );
const double Constants::GRIDSIZE = Constants::HALVE_GRIDSIZE * 2;
const double Constants::HALVE_GRIDSIZE = 5 * Constants::HALVE_CELL_SIZE + 4 * Constants::STEP_SIZE;

const int Constants::COLS = 9;
const int Constants::ROWS = 9;

const double Constants::CANDY_RADIUS = Constants::HALVE_CELL_SIZE - 3;

Component Constants::directionToSt(Direction direction) {
    Component type;
    if (direction == Direction::VERTICAL) type = Component::STRIPED_BOMB_V;
    else type = Component::STRIPED_BOMB_H;
    return type;
}
