/**
 * File : 
 *  gridDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a the entire grid.
 * 
 * Dependencies:
 *  componentDisplay.hpp
 *  candyDisplay.hpp
 *  stripedDisplay.hpp
 *  wrappedDisplay.hpp
 *  wallDisplay.hpp
 *  cellDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "components/componentDisplay.hpp"
#include "components/candyDisplay.hpp"
#include "components/stripedDisplay.hpp"
#include "components/wrappedDisplay.hpp"
#include "components/wallDisplay.hpp"
#include "cellDisplay.hpp"

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
    using CoordPair = std::pair< Point, Point >;
    enum class animations{Pop, Fill, DropDown, DropLeft, DropRight, Swap};
    std::queue< CoordPair > swapQueue;
    std::queue< std::vector<Point> > dropQueue;
    std::queue< std::vector<Point> > popQueue;
    std::queue< std::vector<CoordColour> > fillQueue;
    std::queue<animations> animationQueue;

    bool swapping = false;
public:
    GridDisplay();

    void draw();
    bool inAnimation() const;

    /* Observer Methods */
    void notifyInit(const Point &coord, int type);
    void notifyInsert(const Point &coord, int type);
    void notifyFill(const std::vector<CoordColour> &fill);
    void notifyDrop(const std::vector<Point> &drop, int direction);
    void notifyPop(const std::vector<Point> &pop);
    void notifySwap(const Point &start, const Point &dest);
    void notifyFailedSwap(const Point &start, const Point &dest);
private:
    /* Animations */
    void nextAnimation();
    void performFill();
    void performDrop(int direction);
    void performPop();
    void performSwap();
    void performFailedSwap();
    /* Utility */
    Point calculateCenter(const Point &coord) const;
    std::shared_ptr<ComponentDisplay> factoryMethod(int row, int col, int component) const;
};

#endif