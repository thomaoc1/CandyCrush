#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

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
    using CellMatrix = std::vector< std::vector<CellDisplay> >;
    using ComponentMatrix = std::vector< std::vector< std::shared_ptr<ComponentDisplay> > >;
    using CoordColour = std::pair< Point, int >;
    CellMatrix visualGrid;
    ComponentMatrix visualComponents;
public:
    GridDisplay();
    void draw();
    void notifyInsert(const Point &coord, int type);
    void notifyFill(const std::vector<CoordColour> &fill);
    void notifyDropDown(const std::vector<Point> &drop);
    void notifyDropLeft(const Point &drop);
    void notifyDropRight(const Point &drop);
    void notifyPop(const std::vector<Point> &pop);
    void notifySwap(const Point &start, const Point &dest);
private:
    void componentMove(const Point &start, const Point &dest);
    Point calculateCenter(int row, int col) const;
    std::shared_ptr<ComponentDisplay> factoryMethod(int row, int col, int component) const;
    int associatedColour(int component) const;
    void initialiseGrid();
};

#endif