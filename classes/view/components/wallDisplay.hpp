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

class WallDisplay : public ComponentDisplay {
    const Fl_Color fillColour = FL_BLACK;
public:
    WallDisplay(Point center) : ComponentDisplay(center, Constants::INTER_CELL) {}
    void draw() override {drawShape();}
    void drawShape() const override;
};

#endif