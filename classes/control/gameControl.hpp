#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "../model/grid.hpp"
#include "../view/GUI.hpp"

#include <string>

class GameControl {
    Grid grid;
    GUI view;
public:
    GameControl(const std::string &level) : grid{Grid(level)}, view{grid} {}
    GameControl() : grid{Grid()}, view{grid} {}
    void gameLoop();
};


#endif