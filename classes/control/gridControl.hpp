#ifndef GRIDCONTROL_HPP
#define GRIDCONTROL_HPP

#include "../model/grid.hpp"

#include <FL/Fl.H>

#include <string>

class GridControl {
    std::shared_ptr<Grid> grid;
public:
    GridControl(std::shared_ptr<Grid> grid) : grid{grid} {}
    bool proccessEvent(const int event) {return event;}
    void fill();
    void drop();
    void clean();
    bool clearGrid();
    void gameLoop();
};


#endif