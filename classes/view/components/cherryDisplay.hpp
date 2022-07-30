#ifndef CHERRY_DISPLAY_HPP
#define CHERRY_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/rectangle.hpp"

class CherryDisplay : public ComponentDisplay {
public:
    CherryDisplay(const Point &center) : 
        ComponentDisplay(std::make_shared<Rectangle>(center, Constants::CHERRY, Constants::CELL_SIZE, FL_FLAT_BOX)) {}
    void draw() override {ComponentDisplay::drawShape();}

    // DEBUG
    std::string type() const override {return "C";}
};

#endif