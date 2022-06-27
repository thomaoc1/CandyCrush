#ifndef BOARD_HPP
#define BOARD_HPP

#include "candy.hpp"
#include "wall.hpp"
#include "candyBomb.hpp"

#include <vector>
#include <memory>
#include <iostream>

class Board {
    std::vector< std::vector< std::shared_ptr<Cell> > > board;
public:
    Board();
    std::vector< std::vector< std::string > > package() const;
    void display() const;
private:
    void insertComponent(int row, int col);
    std::vector< std::shared_ptr<Cell> > getNeighbours(int row, int col) const; 
};

#endif