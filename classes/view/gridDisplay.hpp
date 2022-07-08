#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "../model/grid.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include <memory>

class GridDisplay {
    const std::shared_ptr< const Grid > grid;
public:
    GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {}
    void draw() const;
};

#endif