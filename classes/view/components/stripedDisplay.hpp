/**
 * @file stripedDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation of 
 *  a StripedBomb.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef STRIPED_DISPLAY_HPP
#define STRIPED_DISPLAY_HPP

#include "bombDisplay.hpp"

class StripedDisplay : public BombDisplay {
public:
    StripedDisplay(const Point &center, Colour colour, Direction blastDirection) : 
                    BombDisplay(center, colour, blastDirection == Direction::VERTICAL ? std::string{"StV"} : std::string{"StH"}) {}
    StripedDisplay(const StripedDisplay &) = default;
    StripedDisplay(StripedDisplay &&) = default;
};

#endif