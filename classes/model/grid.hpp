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

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

class Grid {
    std::vector< std::vector< Cell > > grid;
public:
    Grid();
    void clean();
    std::vector< std::vector< std::string > > package() const;
    void display() const;
private:
    bool clear();
    bool drop();
    void pop(Cell * target);
    void insertComponent(int row, int col);
    std::vector< std::vector< Cell * > > getNeighbours(int row, int col); 
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current);
};

#endif