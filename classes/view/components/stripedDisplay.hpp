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
#include "../text/textDisplay.hpp"

class StripedDisplay : public ComponentDisplay {
    const int blastDirection;
    TextDisplay text;
public:
    StripedDisplay(const Point &center, int colour, int blastDirection) : 
                    ComponentDisplay(std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)),
                    blastDirection{blastDirection},
                    text{getCenter(), 
                         blastDirection == Constants::VERTICAL ? std::string{"StV"} : std::string{"StH"}, 
                         FL_HELVETICA, 
                         static_cast<int>(getSize() / 1.5)} {}
    StripedDisplay(const StripedDisplay &) = default;
    StripedDisplay(StripedDisplay &&) = default;
    void drawShape() const override;
    
    void setCenter(const Point &dest) override;
    void setSize(int newSize) override;
};

#endif