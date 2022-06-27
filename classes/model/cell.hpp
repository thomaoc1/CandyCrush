#ifndef CELL_HPP
#define CELL_HPP

#include "gameComponent.hpp"

#include <memory>

class Cell {
    std::shared_ptr<GameComponent> occupied;
public:
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
    void setNeighbours(const std::vector< std::shared_ptr<GameComponent> > &nb) {occupied->setNeighbours(nb);}
    std::vector< std::shared_ptr<GameComponent> > getNeighbours() const {return occupied->getNeighbours();}
    std::string package() const {return occupied->package();}
};


#endif 
