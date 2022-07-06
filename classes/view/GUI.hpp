#ifndef FLTKGUI_HPP
#define FLTKGUI_HPP

#include "../model/grid.hpp"

class GUI {
    const Grid &grid;
    typedef std::pair< Point, Point > PointPair;
public:
    GUI (const Grid &grid) : grid{grid} {} 
    PointPair displayTurn() const;
    void displayGrid() const;
};

#endif