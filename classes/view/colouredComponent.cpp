#include "colouredComponent.hpp"

ColouredComponent::ColouredComponent(Point center, int colour) : ComponentDisplay(center) {
    switch(colour) {
        case Constants::RED:
            fl_colour = FL_RED;
            break;        
        case Constants::BLUE:
            fl_colour = FL_BLUE;
            break;
        case Constants::GREEN:
            fl_colour = FL_GREEN;
            break;
        case Constants::PURPLE:
            fl_colour = FL_MAGENTA;
            break;
        case Constants::YELLOW:
            fl_colour = FL_YELLOW;
            break;
        case Constants::ORANGE:
            fl_colour = fl_rgb_color(255,165,0);
            break;
    }
}