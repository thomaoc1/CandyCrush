#include "constants.hpp"

const double Constants::FPS = 60;
const double Constants::WINDOW_HEIGHT = 750;
const double Constants::WINDOW_WIDTH = 750;
const double Constants::GAME_WINDOW_Y = (1.0 / 3.0) * Constants::WINDOW_HEIGHT;
const double Constants::GAME_WINDOW_X = (1.0 / 4.0) * Constants::WINDOW_WIDTH;
const double Constants::INTER_CELL = (1.0/ 4.0) * Constants::GAME_WINDOW_X;
const double Constants::CELL_SIZE = (0.03) * Constants::WINDOW_HEIGHT;

const std::array< int, 6 > Constants::candies = {components::RED, components::BLUE, components::GREEN, 
                                                    components::YELLOW, components::PURPLE, components::ORANGE};