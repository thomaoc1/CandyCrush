#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "../model/grid.hpp"
#include "componentDisplay.hpp"
#include "cellDisplay.hpp"
#include "candyDisplay.hpp"
#include "stripedDisplay.hpp"
#include "wrappedDisplay.hpp"
#include "wallDisplay.hpp"

#include <memory>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class GridDisplay {
    const std::shared_ptr< const Grid > grid;
    using CellMatrix = std::vector< std::vector<CellDisplay> >;
    using ComponentMatrix = std::vector< std::vector< std::shared_ptr<ComponentDisplay> > >;
    CellMatrix visualGrid;
    ComponentMatrix visualComponents;
public:
    GridDisplay(const std::shared_ptr< const Grid > grid);
    void draw();
    void componentSwap(const Point &start, const Point &dest);
private:
    void componentMove(const Point &start, const Point &dest);
    Point calculateCenter(int row, int col) const;
    std::shared_ptr<ComponentDisplay> factoryMethod(int row, int col, int component) const;
    int associatedColour(int component) const;
    void reconstructGrid();
    
};

#endif