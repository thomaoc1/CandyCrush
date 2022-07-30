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
    std::shared_ptr<GridDisplay> view;
    Point click, clickToIndex;
    Point hold, holdToIndex;
    bool dragged = false;



public:
    GridControl(std::shared_ptr<Grid> grid, std::shared_ptr<GridDisplay> view) : grid{grid}, view{view} {} 
    bool proccessEvent(const int event);
private:
    void clickEvent(const Point &mouseLoc);
    bool coordInGame(const Point &mouseLoc) const;
    Point coordToCell(const Point &mouseLoc) const;
    void dragEvent(const Point &mouseLoc);
};


#endif