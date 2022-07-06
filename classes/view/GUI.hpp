#ifndef FLTKGUI_HPP
#define FLTKGUI_HPP

#include "../model/grid.hpp"

class GUI {
    const Grid &grid;
public:
    GUI (const Grid &grid) : grid{grid} {} 
    void displayGrid() const;
};

#endif