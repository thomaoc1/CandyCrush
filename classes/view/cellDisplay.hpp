#ifndef CELL_DISPLAY_HPP
#define CELL_DISPLAY_HPP

#include "componentDisplay.hpp"

#include <memory>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CellDisplay {
    std::shared_ptr<ComponentDisplay> occupied;
    const Fl_Color frameColour = FL_BLACK;
public:
    CellDisplay() {}
    // CellDisplay(std::shared_ptr<ComponentDisplay> occupied) : occupied{occupied} {}
    void setOccupied(std::shared_ptr<ComponentDisplay> component) {occupied = component;}
    void draw(int row, int col) const;
};

#endif