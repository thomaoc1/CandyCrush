#ifndef CELL_DISPLAY_HPP
#define CELL_DISPLAY_HPP

class CellDisplay;

#include "componentDisplay.hpp"
#include "dropAnimation.hpp"

#include <memory>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CellDisplay {
    std::shared_ptr<ComponentDisplay> occupied;
    const Fl_Color frameColour = FL_BLACK;
    const int row, col;
    std::shared_ptr<DropAnimation> currentAnimation;
public:
    CellDisplay(std::shared_ptr<ComponentDisplay> occupied, int row, int col) : occupied{occupied}, row{row}, col{col} {}
    void setOccupied(std::shared_ptr<ComponentDisplay> component) {occupied = component;}
    void unOccupy() {occupied = nullptr;}
    Point getLoc() const {return {row, col};}
    void draw(int animation=Constants::NO_ANIMATION);
    void drawNoAnimation(); 
};

#endif