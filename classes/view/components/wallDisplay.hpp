/**
 * File : 
 *  candyDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a specific gameComponent: "Wall".
 * 
 * Dependencies:
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef WALL_DISPLAY_HPP
#define WALL_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/rectangle.hpp"

class WallDisplay : public ComponentDisplay {
public:
    WallDisplay(Point center) : 
        ComponentDisplay(std::make_shared<Rectangle>(center, Constants::WALL, Constants::INTER_CELL, FL_FLAT_BOX)) {}
    void draw() override {ComponentDisplay::drawShape();}

    std::string type() const override {return "#";}
};

#endif