#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "../model/grid.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

#include <memory>
#include "../model/actions/events.hpp"

class GridDisplay {
    const std::shared_ptr< const Grid > grid;
    Events events;
public:
    GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {}
    void draw();
private:
    void drawCell(int x, int y) const;
    void drawCandy(int colour, int x, int y) const;
    void drawWrappedBomb(int colour, int x, int y) const;
    void drawStripedBomb(int colour, int x, int y) const;
    void drawWall(int x, int y) const;
};

#endif