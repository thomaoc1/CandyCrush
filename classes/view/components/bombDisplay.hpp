/**
 * @file candyDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is generalises the graphical representation of 
 *  a Bombs.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef BOMB_DISPLAY_HPP
#define BOMB_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"
#include "../text/text.hpp"

class BombDisplay : public ComponentDisplay {
    Text text;
public:
    BombDisplay(const Point &center, Colour colour, const std::string &type)
        : ComponentDisplay{std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)},
            text{getCenter(), type, FL_HELVETICA, static_cast<int>(getSize() / 1.5)} {}

    virtual void drawShape() const override;
    virtual void setCenter(const Point &dest) override;
    virtual void setSize(double newSize) override;
};

#endif