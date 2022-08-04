/**
 * File : 
 *  gridControl.hpp
 *
 * Decription :
 *  Handles events and makes changes to the grid when necessary
 * 
 * Dependencies : 
 *  grid.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef GRIDCONTROL_HPP
#define GRIDCONTROL_HPP

#include "../model/containers/grid.hpp"
#include "../shared/log.hpp"

#include <FL/Fl.H>

#include <string>

class GridControl {
    std::shared_ptr<Grid> grid;
    const GridDisplay &view;
    Point click, clickToIndex;
    Point hold, holdToIndex;
    bool dragged = false;

public:
    GridControl(std::shared_ptr<Grid> grid, const GridDisplay &view) : grid{grid}, view{view} {} 
    GridControl(const GridDisplay &view) : view{view} {}
    bool proccessEvent(const int event);
    void associateGrid(std::shared_ptr<Grid> newGrid) {grid = newGrid;}
private:
    void clickEvent(const Point &mouseLoc);
    bool coordInGame(const Point &mouseLoc) const;
    Point coordToCell(const Point &mouseLoc) const;
    void dragEvent(const Point &mouseLoc);
};


#endif