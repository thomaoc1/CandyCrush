#include "wrappedBomb.hpp"

int WrappedBomb::type() const {
    int repr;
    switch (getColour()) {
        case Constants::RED:
            repr = Constants::RED_WRAPPED_BOMB;
            break;
        case Constants::BLUE:
            repr = Constants::BLUE_WRAPPED_BOMB;
            break;
        case Constants::GREEN:
            repr = Constants::GREEN_WRAPPED_BOMB;
            break;
        case Constants::YELLOW:
            repr = Constants::YELLOW_WRAPPED_BOMB;
            break;
        case Constants::PURPLE:
            repr = Constants::PURPLE_WRAPPED_BOMB;
            break;
        case Constants::ORANGE:
            repr = Constants::ORANGE_STRIPED_BOMB;
            break;
        
    }
    return repr;
}