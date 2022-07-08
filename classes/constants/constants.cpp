#include "constants.hpp"

const double Constants::FPS = 60;
const double Constants::WINDOW_HEIGHT = 750;
const double Constants::WINDOW_WIDTH = 750;
const double Constants::GAME_WINDOW_Yi = (1.0 / 3.0) * Constants::WINDOW_HEIGHT;
const double Constants::GAME_WINDOW_Xi = (1.0 / 4.0) * Constants::WINDOW_WIDTH;
const double Constants::GAME_WINDOW_Yf = 8 * Constants::INTER_CELL + Constants::GAME_WINDOW_Yi;
const double Constants::GAME_WINDOW_Xf = 8 * Constants::INTER_CELL + Constants::GAME_WINDOW_Xi;
const double Constants::INTER_CELL = (1.0 / 4.0) * Constants::GAME_WINDOW_Xi;
const double Constants::CELL_SIZE = (0.03) * Constants::WINDOW_HEIGHT;

const std::array< int, 6 > Constants::candies = {components::RED, components::BLUE, components::GREEN, 
                                                    components::YELLOW, components::PURPLE, components::ORANGE};