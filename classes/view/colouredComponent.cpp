#include "colouredComponent.hpp"

ColouredComponent::ColouredComponent(int colour) {
    switch(colour) {
        case Constants::RED:
            colour = FL_RED;
            break;        
        case Constants::BLUE:
            colour = FL_BLUE;
            break;
        case Constants::GREEN:
            colour = FL_GREEN;
            break;
        case Constants::PURPLE:
            colour = FL_MAGENTA;
            break;
        case Constants::YELLOW:
            colour = FL_YELLOW;
            break;
        case Constants::ORANGE:
            colour = fl_rgb_color(255,165,0);
            break;
    }
}