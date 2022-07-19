#ifndef GRIDCONTROL_HPP
#define GRIDCONTROL_HPP

#include "../model/grid.hpp"

#include <FL/Fl.H>

#include <string>

class GridControl {
    std::shared_ptr<Grid> grid;
    Point click, clickToIndex;
    Point hold, holdToIndex;
    bool clicked = false;
public:
    GridControl(std::shared_ptr<Grid> grid) : grid{grid} {}
    bool proccessEvent(const int event);
    void fill();
    void drop();
    void clean();
    bool clearGrid();
private:
    void clickEvent(const Point &mouseLoc);
    bool coordInGame(const Point &mouseLoc) const;
    Point coordToCell(const Point &mouseLoc) const;
    void dragEvent(const Point &mouseLoc);
};


#endif