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

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"
#include "../text/textDisplay.hpp"

class WrappedDisplay : public ComponentDisplay {
public:
    WrappedDisplay(const Point &center, int colour) : ComponentDisplay(std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)) {}
    WrappedDisplay(const WrappedDisplay &) = default;
    WrappedDisplay(WrappedDisplay &&) = default;
    void drawShape() const override;
};

#endif