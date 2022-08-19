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

#include "../../common/enumerations.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {
    using CellMatrix = std::vector< std::vector< Cell > >;
    CellMatrix grid;

    using CellComponent = std::pair< Cell *, ComponentType >;

    std::vector< CellComponent > bombs;

    GridDisplay &observer;
    
    std::vector< Cell * > toPop; 
    std::vector< Cell * > specialBombs;

    FileHandler fh;
    GameData gd;
    GameObjective gameObj;
    Score score;

    const int ROWS = Constants::ROWS;
    const int COLS = Constants::COLS;

    class Nbs {
        std::vector<Cell *> vert;
        std::vector<Cell *> horiz;
    public:
        Nbs() = default;

        void set(std::vector<Cell *> &&newVert, std::vector<Cell *> &&newHoriz) 
            {vert = std::move(newVert); horiz = std::move(newHoriz);}      

        std::vector<Cell *> get(Direction dir) const {return dir == Direction::VERTICAL ? vert : horiz;}
        bool validity() const {return vert.size() >= 3 || horiz.size() >= 3;}
        int size(Direction dir) const {return dir == Direction::VERTICAL ? vert.size() : horiz.size();}
    };

    enum CompType{Normal, Striped, Wrapped, Special};
    struct BombInfo {
        CompType type = Normal;
        Direction direction = Direction::VERTICAL;
        int index = -1;
    };

public:
    Grid(GridDisplay &observer) : observer{observer}, gameObj{observer}, score{observer} {initialiseCells();}
    Grid(const Grid &) = default;
    Grid(Grid &&) = delete;

    void setLevel(const std::string &level);
    void swap(const Point &cell1, const Point &cell2);
    GameState gameState() const {return gameObj.gameState();}

private:
    /* Init */
    void initialiseCells();
    void completeGrid();

    void fileInterpreter();

    /* Grid Cleaning */
    void wrBombExtract(const std::vector< Cell * > &cColour, int index, Direction direction);
    void stBombExtract(Cell &cell, Direction direction);
    void spBombExtract(Cell &cell) {bombs.push_back({&cell, ComponentType{Colour::DARK_RED, Component::SPECIAL_BOMB}});}
    void bombExtract(Cell &cell, const std::vector< Cell * > &cColour, const BombInfo &b);
    void clearCheck(Cell &cell);

    /* Insertion / Suppression */
    void wrappedBlast(Cell &target);
    void stripedBlast(Cell &target);
    void specialBlast(Cell &c1, Cell &c2);
    void wrStBlast(Cell &c1);
    void bombSwap(Cell &c1, Cell &c2);
    void unoccupy(Cell &target);
    void clearFrostings();
    void popAll();
    void willPop(Cell &target);
    void popIngredient();
    void insertComponent(int row, int col);
    void insertComponent(const Point &coord) {insertComponent(coord.y, coord.x);}
    void insertComponent(Cell &cell, const ComponentType &type);
    void placeBombs();
    void exchangeCells(Cell &c1, Cell &c2);
    bool fillTop();
    void refillGrid();
    /** Repeatedly fills top row */
    void completeFill() {while(fillTop()) completeDrop();}
    bool clear();
    bool directedDrop(Beneath direction);
    void completeDrop();
    void clean(Cell &c1, Cell &c2);
    void clean();
    bool checkSwap(const Point &cell1, const Point &cell2);
    bool checkSwap(Cell &cell1, Cell &cell2) {return checkSwap(cell1.getLocation(), cell2.getLocation());}

    /* Sequential colour fetching */
    std::vector< Cell * > colourDFS(Cell &initial, Direction orientation) const; 
    Nbs continuousColour(Cell &current) const;

    /* Neighbour Fetching */
    std::vector< Cell * > getNbs(int row, int col);

    /* Conditions */
    bool isOccupied(const Cell &cell) {return cell.getOccupied() ? true : false;}
    bool possibleMoves();
    bool inGrid(const Point &coord) const;
    bool sameBomb(Cell &c1, Cell &c2) const;
    bool isMobile(Component component) const;
    bool canPop(Component component) const;
    // Swap checks
    bool bombSwapCheck(Cell &c1, Cell &c2) const;
    bool specialSwapCheck(Cell &c1, Cell &c2) const;
    // Spawn checks
    bool spSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 5;}
    int wrSpawnCond(const std::vector< Cell * > &cColour, Direction direction) const;
    bool stSpawnCond(const std::vector< Cell * > &cColour) const {return static_cast<int>(cColour.size()) == 4;}
    // Blast conditions
    bool spBlastCond(Cell &c) const {return c.getBlastType() == BlastType::SPECIAL;}
    bool wrBlastCond(Cell &c) const {return c.getBlastType() == BlastType::WRAPPED;}
    bool stBlastCond(Cell &c) const {return c.getBlastType() == BlastType::STRIPED;}

    /* Utility */
    Direction perpendicular(Direction dir) const;
};

#endif