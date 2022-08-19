/**
 * @file wallDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation of 
 *  a Wall.
 * 
 * @version 0.1
 * @date 2022-08-19
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