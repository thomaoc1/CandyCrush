#include "constants.hpp"

const double Constants::FPS = 1;
const double Constants::WINDOW_HEIGHT = 750;
const double Constants::WINDOW_WIDTH = 750;
const double Constants::GAME_WINDOW_Yi = (1.0 / 3.0) * Constants::WINDOW_HEIGHT;
const double Constants::GAME_WINDOW_Xi = (0.2) * Constants::WINDOW_WIDTH;
const double Constants::GAME_WINDOW_Yf = 8 * Constants::INTER_CELL + Constants::GAME_WINDOW_Yi;
const double Constants::GAME_WINDOW_Xf = 8 * Constants::INTER_CELL + Constants::GAME_WINDOW_Xi;
const double Constants::INTER_CELL = (0.325) * Constants::GAME_WINDOW_Xi;
const double Constants::CANDY_RADIUS = (0.05) * (Constants::GAME_WINDOW_Yf - Constants::GAME_WINDOW_Yi);

const std::array< int, 6 > Constants::candies = {components::RED, components::BLUE, components::GREEN, 
                                                    components::YELLOW, components::PURPLE, components::ORANGE};