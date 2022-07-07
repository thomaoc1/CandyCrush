#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "../model/grid.hpp"
#include "../view/terminalGui.hpp"
#include "../view/mainWindow.hpp"

#include <FL/Fl.H>

#include <string>

class GridControl {
    std::shared_ptr<Grid> grid;
public:
    GridControl(std::shared_ptr<Grid> grid) : grid{grid} {}
    void fill();
    void drop();
    void clean();
    bool clearGrid();
    void gameLoop();
};


#endif