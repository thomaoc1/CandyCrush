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

#include "bombDisplay.hpp"

class StripedDisplay : public BombDisplay {
public:
    StripedDisplay(const Point &center, int colour, int blastDirection) : 
                    BombDisplay(center, colour, blastDirection == Constants::VERTICAL ? std::string{"StV"} : std::string{"StH"}) {}
    StripedDisplay(const StripedDisplay &) = default;
    StripedDisplay(StripedDisplay &&) = default;
};

#endif