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
#include "../components/cherry.hpp"
#include "../components/hazelnut.hpp"
#include "../components/frosting.hpp"
#include "../filehandler/fileHandler.hpp"
#include "../../shared/point.hpp"
#include "../score.hpp"
#include "../gameObjective.hpp"

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

    GridDisplay &observer;
    
    std::vector< Cell * > toPop; 
    std::vector< Cell * > specialBombs;

    GameData gd;
    GameObjective go;
    Score score;


    const int ROWS = Constants::ROWS;
    const int COLS = Constants::COLS;

public:
    Grid(GridDisplay &observer, const std::string &level);
    void swap(const Point &cell1, const Point &cell2);

private:

    void fileInterpreter();

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
    void specialBlast(Cell * c1, Cell * c2);
    void wrStBlast(Cell * c1);
    void bombSwap(Cell * c1, Cell * c2);
    void unoccupy(Cell * target);
    void clearFrostings();
    void popAll();
    void willPop(Cell * target);
    void popIngredient();
    void insertComponent(int row, int col);
    void insertComponent(const Point &coord) {insertComponent(coord.y, coord.x);}
    void insertComponent(Cell * cell, int type);
    void placeWrappedCandies();
    void placeStripedCandies();
    void placeSpecialBombs();
    void exchangeCells(Cell * c1, Cell * c2);

    /* Grid manipulation */
    bool fillTop();
    void refillGrid();
    /** Repeatedly fills top row */
    void completeFill() {while(fillTop()) completeDrop();}
    bool clear();
    bool directedDrop(int direction);
    void completeDrop();
    void clean(Cell * c1, Cell * c2);
    void clean();
    bool checkSwap(const Point &cell1, const Point &cell2);
    bool checkSwap(Cell * cell1, Cell * cell2) {return checkSwap(cell1->getLocation(), cell2->getLocation());}

    /* Sequential colour fetching */
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current) const;

    /* Neighbour Fetching */
    std::vector< Cell * > getNbs(int row, int col);

    /* Conditions */
    bool possibleMoves();
    bool inGrid(const Point &coord) const;
    bool sameBomb(Cell * c1, Cell * c2) const;
    bool isMobile(int component) const;
    bool canPop(int component) const;
    // bool canPop(int component) const {return !(component == Constants::CHERRY || component == Constants::HAZELNUT);}
    // Swap checks
    bool bombSwapCheck(Cell * c1, Cell * c2) const;
    bool specialSwapCheck(Cell * c1, Cell * c2) const;
    // Spawn checks
    bool spSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 5;}
    int wrSpawnCond(const std::vector< Cell * > &cColour, int direction) const;
    bool stSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 4;};
    // Blast conditions
    bool spBlastCond(Cell * c) const {return c->getBlastType() == Constants::SPECIAL;}
    bool wrBlastCond(Cell * c) const {return c->getBlastType() == Constants::WRAPPED;}
    bool stBlastCond(Cell * c) const {return c->getBlastType() == Constants::STRIPED;}
    // TEMP
    void package() const;
};

#endif