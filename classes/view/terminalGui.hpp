#ifndef VIEW_TERMINAL_HPP
#define VIEW_TERMINAL_HPP

#include "../model/grid.hpp"

class TerminalGui {
    const Grid &grid;
    typedef std::pair< Point, Point > PointPair;
public:
    TerminalGui (const Grid &grid) : grid{grid} {} 
    PointPair displayTurn() const;
    void displayGrid() const;
};

#endif