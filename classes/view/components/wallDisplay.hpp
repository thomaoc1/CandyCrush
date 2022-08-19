/**
 * File : 
 *  wallDisplay.hpp
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
    WallDisplay(const Point &center)
        : ComponentDisplay(std::make_shared<Rectangle>(center, Colour::BLACK,
                                                        Constants::CELL_SIZE, FL_FLAT_BOX)) {}
    void draw() override {ComponentDisplay::drawShape();}
};

#endif