#include "gameComponent.hpp"

std::string GameComponent::toString() const {
        std::string ret;
        switch (colour) {
            case Constants::RED:
                ret = "R";
                break; 
            case Constants::BLUE:
                ret = "B";
                break;
            case Constants::GREEN:
                return "G";
                break;
            case Constants::PURPLE:
                ret = "P";
                break;
            case Constants::YELLOW:
                ret = "Y";
                break;
            case Constants::ORANGE:
                ret = "O";
                break;
            case Constants::NONE:
                ret = "#";
                break;
        }
        return ret;
    }