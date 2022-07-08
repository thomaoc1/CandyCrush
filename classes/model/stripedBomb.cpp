#include "stripedBomb.hpp"

int StripedBomb::package() const {
    int repr;
    switch (getColour()) {
        case Constants::RED:
            repr = Constants::RED_STRIPED_BOMB;
            break;
        case Constants::BLUE:
            repr = Constants::BLUE_STRIPED_BOMB;
            break;
        case Constants::GREEN:
            repr = Constants::GREEN_STRIPED_BOMB;
            break;
        case Constants::YELLOW:
            repr = Constants::YELLOW_STRIPED_BOMB;
            break;
        case Constants::PURPLE:
            repr = Constants::PURPLE_STRIPED_BOMB;
            break;
        case Constants::ORANGE:
            repr = Constants::ORANGE_STRIPED_BOMB;
            break;
        
    }
    return repr;
}