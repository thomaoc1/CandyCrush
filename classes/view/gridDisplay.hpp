#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "cellDisplay.hpp"
#include "candyDisplay.hpp"
#include "stripedDisplay.hpp"
#include "wrappedDisplay.hpp"
#include "wallDisplay.hpp"

#include <memory>
#include <vector>
#include <queue>
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class GridDisplay {
    using CellMatrix = std::vector< std::vector<CellDisplay> >;
    CellMatrix visualGrid;
    
    using ComponentMatrix = std::vector< std::vector< std::shared_ptr<ComponentDisplay> > >;
    ComponentMatrix visualComponents;
    
    using CoordColour = std::pair< Point, int >;
    enum class animations{Pop, Fill, DropDown, DropLeft, DropRight};
    std::queue< std::vector<Point> > dropQueue;
    std::queue< std::vector<Point> > popQueue;
    std::queue< std::vector<CoordColour> > fillQueue;
    std::queue<animations> animationQueue;
public:
    GridDisplay();
    void draw();
    void notifyInit(const Point &coord, int type);
    void notifyInsert(const Point &coord, int type);
    
    void notifyFill(const std::vector<CoordColour> &fill);
    void notifyDrop(const std::vector<Point> &drop, int direction);
    void notifyPop(const std::vector<Point> &pop);
    void notifySwap(const Point &start, const Point &dest);
private:
    void nextAnimation();
    void performFill();
    void performDrop(int direction);
    void performPop();
    void performSwap(const Point &start, const Point &dest);

    void componentMove(const Point &start, const Point &dest);
    Point calculateCenter(const Point &coord) const;
    std::shared_ptr<ComponentDisplay> factoryMethod(int row, int col, int component) const;
    int associatedColour(int component) const;
    void initialiseGrid();
};

#endif