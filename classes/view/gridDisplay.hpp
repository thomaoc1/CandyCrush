#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "../model/actions/events.hpp"
#include "../model/grid.hpp"
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
    Events events;
    std::vector< std::vector<CellDisplay> > visualGrid;
public:
    GridDisplay(const std::shared_ptr< const Grid > grid);
    void draw();
private:
    void reconstructGrid();
    void drawCell(int x, int y) const;
    void drawCandy(int colour, int x, int y) const;
    void drawWrappedBomb(int colour, int x, int y) const;
    void drawStripedBomb(int colour, int x, int y) const;
    void drawWall(int x, int y) const;
};

#endif