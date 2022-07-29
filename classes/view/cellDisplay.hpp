/**
 * File : 
 *  cellDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a gameComponent container.
 * 
 * Dependencies:
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef CELL_DISPLAY_HPP
#define CELL_DISPLAY_HPP

#include "components/componentDisplay.hpp"
#include "shapes/rectangle.hpp"

#include <memory>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>


class CellDisplay : public ComponentDisplay {
public:
    CellDisplay(const Point &center)
        : ComponentDisplay(std::make_shared<Rectangle>(center, Constants::WALL, Constants::INTER_CELL, FL_BORDER_FRAME)) {}
    void draw() override {drawShape();}
};

#endif