/**
 * File : 
 *  grid.hpp
 * 
 * Decription :
 *  Class which groups Cells and GameComponents to represent the state of 
 *  a CandyCrush match
 * 
 * Dependencies :
 *  Model
 *      cell.hpp
 *      candy.hpp
 *      wall.hpp
 *      wrappedBomb.hpp
 *      stripedBomb.hpp
 *      point.hpp
 *  View
 *      gridDisplay.hpp
 * 
 * Authors : 
 *  Thomas O'Cuilleanain, 
 *  Marcus Chretirn
 */ 

#ifndef BOARD_HPP
#define BOARD_HPP

#include "cell.hpp"
#include "../components/candy.hpp"
#include "../components/wall.hpp"
#include "../components/wrappedBomb.hpp"
#include "../components/stripedBomb.hpp"
#include "../../shared/point.hpp"

#include "../../view/gridDisplay.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {
    using CellMatrix = std::vector< std::vector< Cell > >;
    CellMatrix grid;

    using CellIntPair = std::pair< Cell *, int >;
    std::vector< CellIntPair > stripedBombs;
    std::vector< CellIntPair > wrappedBombs;

    std::shared_ptr<GridDisplay> observer;
    
    std::vector< Cell * > toPop; 
    std::vector< Cell * > specialBombs;
public:
    // I dont like this lol
    static const int COLS = 9;
    static const int ROWS = 9;

    Grid(std::shared_ptr<GridDisplay> observer);
    Grid(std::shared_ptr<GridDisplay> observer, const std::string &level);
    int getCell(int y, int x) const {return grid[y][x].type();}
    void swap(const Point &cell1, const Point &cell2);
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
    void exchangeCells(Cell * c1, Cell * c2);

    /* Grid manipulation */
    bool fillTop();
    void completeFill();
    bool clear();
    bool directedDrop(int direction);
    void completeDrop();
    void clean();
    bool checkSwap(const Point &cell1, const Point &cell2);

    /* Sequential colour fetching */
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current);

    /* Neighbour Fetching */
    std::vector< std::vector< Cell * > > getCrossNbs(int row, int col);
    std::vector< Cell * > getBelowNbs(int row, int col);

};

#endif