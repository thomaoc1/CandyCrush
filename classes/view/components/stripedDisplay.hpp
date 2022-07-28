/**
 * File : 
 *  stripedDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a specific gameComponent: "Striped Candy Bomb".
 * 
 * Dependencies:
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef STRIPED_DISPLAY_HPP
#define STRIPED_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"

class StripedDisplay : public ComponentDisplay {
    const int blastDirection;
public:
    StripedDisplay(const Point &center, int colour, int blastDirection) : 
                    ComponentDisplay(std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)),
                    blastDirection{blastDirection} {}
    StripedDisplay(const StripedDisplay &) = default;
    StripedDisplay(StripedDisplay &&) = default;
    void drawShape() const override;
};

#endif