/**
 * File : 
 *  grid.hpp
 * 
 * Decription :
 *  Class which groups Cells and GameComponents to represent the state of 
 *  a CandyCrush match
 * 
 * Authors : 
 *  Thomas O'Cuilleanain, 
 *  Marcus Chretirn
 */ 

#ifndef BOARD_HPP
#define BOARD_HPP

#include "cell.hpp"
#include "candy.hpp"
#include "wall.hpp"
#include "wrappedBomb.hpp"
#include "stripedBomb.hpp"
#include "actions/events.hpp"
#include "actions/action.hpp"
#include "actions/suppression.hpp"
#include "actions/displacement.hpp"
#include "actions/swap.hpp"
#include "point.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {
    std::vector< std::vector< Cell > > grid;
    Events events;
    typedef std::pair< Cell *, int > CellIntPair;
    std::vector< CellIntPair > stripedBombs;
    std::vector< CellIntPair > wrappedBombs;
    std::vector< Cell * > toPop; 
    std::vector< Cell * > specialBombs;
public:
    // I dont like this lol
    static const int COLS = 9;
    static const int ROWS = 9;

    Grid();
    Grid(const std::string &level);
    /* Grid manipulation */
    bool fill();
    bool clear();
    bool directedDrop(int direction);
    bool checkSwap(const Point &cell1, const Point &cell2);
    int getCell(int y, int x) const {return grid[y][x].package();}
    bool occurence() const {return events.occurrence();}
    Events getEvents() const {return events;}
    void resetEvents() {events.reset();}
private:
    /* Grid Cleaning */
    bool wrappedBomb(const std::vector< Cell * > &cColour, int direction);
    bool stripedBomb(Cell * cell, const std::vector< Cell * > &cColour);
    bool specialBomb(Cell * cell, const std::vector< Cell * > &cColour);
    void clearCheck(Cell * cell, int direction);
    /* Insertion / Suppression */
    void pop(Cell * target);
    void popAll();
    
    void insertComponent(int row, int col);
    void insertComponent(Cell * cell, int type);
    void placeWrappedCandies();
    void placeStripedCandies();
    void swap(Cell * c1, Cell * c2);
    /* Sequential colour fetching */
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current);
    /* Neighbour Fetching */
    std::vector< std::vector< Cell * > > getCrossNbs(int row, int col);
    std::vector< Cell * > getBelowNbs(int row, int col);

};

#endif