#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "../model/grid.hpp"
#include "../view/terminalGui.hpp"

#include <string>

class GameControl {
    Grid grid;
    TerminalGui view;
public:
    GameControl(const std::string &level) : grid{Grid(level)}, view{grid} {}
    GameControl() : grid{Grid()}, view{grid} {}
    void fill();
    void drop();
    void clean();
    bool clearGrid();
    void gameLoop();
};


#endif