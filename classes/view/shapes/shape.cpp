#include "shape.hpp"


/**
 * @brief Deduces FL_Color based on Model enum 
 * 
 * @param colour 
 * @return Fl_Color 
 */
Fl_Color Shape::associatedFLColour(Colour colour) const {
    Fl_Color fl_colour;
    switch(colour) {
        case Colour::RED:
            fl_colour = FL_RED;
            break;        
        case Colour::BLUE:
            fl_colour = FL_BLUE;
            break;
        case Colour::GREEN:
            fl_colour = FL_GREEN;
            break;
        case Colour::PURPLE:
            fl_colour = FL_MAGENTA;
            break;
        case Colour::YELLOW:
            fl_colour = FL_YELLOW;
            break;
        case Colour::ORANGE:
            fl_colour = fl_rgb_color(255,165,0);
            break;
        case Colour::DARK_RED:
            fl_colour = FL_DARK_RED;
            break;
        case Colour::BROWN:
            fl_colour = fl_rgb_color(204,82,0);
            break;
        case Colour::CYAN:
            fl_colour = FL_CYAN;
            break;
        default:
            fl_colour = FL_BLACK;
            break;
    }
    return fl_colour;
}