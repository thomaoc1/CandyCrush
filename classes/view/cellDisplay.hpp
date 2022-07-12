#ifndef CELL_DISPLAY_HPP
#define CELL_DISPLAY_HPP

#include "componentDisplay.hpp"

#include <memory>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CellDisplay : public ComponentDisplay {
    const Fl_Color frameColour = FL_BLACK;
    const Point center;
public:
    CellDisplay(const Point &center) : ComponentDisplay(center) {}
    void draw() override {drawShape();}
    void drawShape() const override;
};

#endif