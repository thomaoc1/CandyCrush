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
public:
    Grid();
    void clean();
    bool checkSwap(const Point &cell1, const Point &cell2);
    std::vector< std::vector< std::string > > package() const;
    void display() const;
private:
    void fill();
    void swap(Cell * c1, Cell * c2);
    bool clear();
    void drop();
    bool dropDown();
    bool dropLeft();
    bool dropRight();
    void pop(Cell * target);
    void insertComponent(int row, int col);
    std::vector< std::vector< Cell * > > getCrossNbs(int row, int col);
    std::vector< Cell * > getBelowNbs(int row, int col);
    std::vector< Cell * > colourDFS(Cell * initial, int orientation) const; 
    std::vector< std::vector< Cell * > > continuousColour(Cell * current);
};

#endif