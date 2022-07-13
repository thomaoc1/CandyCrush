#include "constants.hpp"

const double Constants::FPS = 60;
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

int Constants::associatedColour(int component) {
    int colour;
    switch (component) {
        case Constants::RED_STRIPED_BOMB:
        case Constants::RED_WRAPPED_BOMB:
            colour = Constants::RED;
            break;
        case Constants::BLUE_STRIPED_BOMB:
        case Constants::BLUE_WRAPPED_BOMB:
            colour = Constants::BLUE;
            break;
        case Constants::GREEN_STRIPED_BOMB:
        case Constants::GREEN_WRAPPED_BOMB:
            colour = Constants::GREEN;
            break;
        case Constants::YELLOW_STRIPED_BOMB:
        case Constants::YELLOW_WRAPPED_BOMB:
            colour = Constants::YELLOW;
            break;
        case Constants::PURPLE_STRIPED_BOMB:
        case Constants::PURPLE_WRAPPED_BOMB:
            colour = Constants::PURPLE;
            break;
        case Constants::ORANGE_STRIPED_BOMB:
        case Constants::ORANGE_WRAPPED_BOMB:
            colour = Constants::ORANGE;
            break;
        default:
            colour = Constants::NONE;
            break;
    }
    return colour;
}