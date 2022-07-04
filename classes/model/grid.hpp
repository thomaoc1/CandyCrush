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
    bool clear();
    std::vector< std::vector< std::string > > package() const;
    void display();
private:
    void pop(Cell * target);
    void insertComponent(int row, int col);
    std::pair< std::vector< Cell * >, std::vector< Cell * > > getNeighbours(int row, int col); 
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::pair< std::vector< Cell * >, std::vector< Cell * > > continuousColour(Cell * current);
};

#endif