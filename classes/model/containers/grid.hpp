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
#include "../components/specialBomb.hpp"
#include "../filehandler/fileHandler.hpp"
#include "../../shared/point.hpp"

#include "../../view/gridDisplay.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {

    using CellMatrix = std::vector< std::vector< Cell > >;
    CellMatrix grid;

    using CellIntInt = std::pair< Cell *, std::pair< int, int > >;
    using CellIntPair = std::pair< Cell *, int >;
    std::vector< CellIntInt > stripedBombs;
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
    void wrBombExtract(const std::vector< Cell * > &cColour, int index, int direction);
    void stBombExtract(Cell * cell, int direction);
    void spBombExtract(Cell * cell);
    using BombInfo = std::array<int, 3>;
    void bombExtract(Cell * cell, const std::vector< Cell * > &cColour, const BombInfo &b);
    void clearCheck(Cell * cell);

    /* Insertion / Suppression */
    void wrappedBlast(Cell * target);
    void stripedBlast(Cell * target);
    void pop(Cell * target);
    void popAll();
    void willPop(Cell * target);
    void insertComponent(int row, int col);
    void insertComponent(Cell * cell, int type);
    void placeWrappedCandies();
    void placeStripedCandies();
    void placeSpecialBombs();
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
    std::vector< std::vector< Cell * > > continuousColour(Cell * current) const;

    /* Neighbour Fetching */
    std::vector< Cell * > getNbs(int row, int col);

    /* Utility */ 
    bool inGrid(const Point &coord) const;

    /* Conditions */
    bool spSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 5;}
    int wrSpawnCond(const std::vector< Cell * > &cColour, int direction) const;
    bool stSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 4;};

    bool spBlastCond(Cell * c) const {return c->getOccupied()->getBlastType() == Constants::SPECIAL;}
    bool wrBlastCond(Cell * c) const {return c->getOccupied()->getBlastType() == Constants::WRAPPED;}
    bool stBlastCond(Cell * c) const {return c->getOccupied()->getBlastType() == Constants::STRIPED;}

    // TEMP
    void package() const;
};

#endif