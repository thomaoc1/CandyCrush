#ifndef HAZELNUT_DISPLAY_HPP
#define HAZELNUT_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/rectangle.hpp"

class HazelnutDisplay : public ComponentDisplay {
public:
    HazelnutDisplay(const Point &center) : 
        ComponentDisplay(std::make_shared<Rectangle>(center, Constants::HAZELNUT, Constants::INTER_CELL, FL_FLAT_BOX)) {}
    void draw() override {ComponentDisplay::drawShape();}

    std::string type() const override {return "H";}
};

#endif