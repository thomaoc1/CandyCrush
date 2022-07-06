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
#include "candyBomb.hpp"
#include "point.hpp"

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {
    std::vector< std::vector< Cell > > grid;

    typedef std::pair< Cell *, std::string > CellStringPair;
    std::vector< CellStringPair > stripedBombs;
    std::vector< CellStringPair > wrappedBombs;
    std::vector< Cell * > toPop; 
    std::vector< Cell * > specialBombs;
public:
    Grid();
    Grid(const std::string &level);
    bool fill();
    bool clear();
    // void clean();
    bool directedDrop(int direction);
    bool checkSwap(const Point &cell1, const Point &cell2);
    /* Packaging */
    std::vector< std::vector< std::string > > package() const;
    void display() const;
private:
    /* Grid Cleaning */
    bool wrappedBomb(const std::vector< Cell * > &cColour, int direction);
    bool stripedBomb(Cell * cell, const std::vector< Cell * > &cColour);
    bool specialBomb(Cell * cell, const std::vector< Cell * > &cColour);
    std::vector< Cell * > clearCheck(Cell * cell, int direction);
    /* Insertion / Suppression */
    void pop(Cell * target);
    void popAll();
    void insertComponent(int row, int col);
    void insertComponent(Cell * cell, const std::string type, const std::string &colour);
    void swap(Cell * c1, Cell * c2);
    /* Sequential colour fetching */
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current);
    /* Neighbour Fetching */
    std::vector< std::vector< Cell * > > getCrossNbs(int row, int col);
    std::vector< Cell * > getBelowNbs(int row, int col);

};

#endif