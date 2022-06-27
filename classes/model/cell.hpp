#ifndef CELL_HPP
#define CELL_HPP

#include "../constants/constants.hpp"

#include <string>
#include <vector>
#include <memory>

class Cell {
    std::vector< std::shared_ptr<Cell> > neighbours;
public:
    virtual ~Cell() {};
    virtual std::string package() const=0;
    virtual void setNeighbours(const std::vector< std::shared_ptr<Cell> > &nbs) {neighbours = nbs;}
    virtual std::vector< std::shared_ptr<Cell> > getNeighbours() const {return neighbours;}
};

#endif