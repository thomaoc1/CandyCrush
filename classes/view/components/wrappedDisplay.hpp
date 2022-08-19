/**
 * File : 
 *  candyDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a specific gameComponent: "Wrapped Candy Bomb".
 * 
 * Dependencies:
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef WRAPPED_DISPLAY_HPP
#define WRAPPED_DISPLAY_HPP

#include "bombDisplay.hpp"

class WrappedDisplay : public BombDisplay {
public:
    WrappedDisplay(const Point &center, Colour colour) : BombDisplay(center, colour, "Wr") {}
    WrappedDisplay(const WrappedDisplay &) = default;
    WrappedDisplay(WrappedDisplay &&) = default;
};

#endif