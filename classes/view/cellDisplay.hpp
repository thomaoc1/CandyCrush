/**
 * @file cellDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation of 
 *  a Cell.
 * 
 * @version 0.1
 * @date 2022-08-19
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
        : ComponentDisplay(std::make_shared<Rectangle>(center, Colour::BLACK, 
                                                        Constants::CELL_SIZE, FL_BORDER_FRAME)) {}
    void draw() override {drawShape();}
};

#endif