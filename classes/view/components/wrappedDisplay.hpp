/**
 * @file wrappedDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of 
 *  a WrappedBomb.
 * 
 * @version 0.1
 * @date 2022-08-19
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