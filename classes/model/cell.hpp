#ifndef CELL_HPP
#define CELL_HPP

#include "gameComponent.hpp"

#include <memory>

class Cell {
    std::shared_ptr<GameComponent> occupied;
    std::vector< Cell * > neighbours;
public:
    /* Setters */
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    void setNeighbours(const std::vector< Cell * > &nbs) {neighbours = nbs;}
    
    /* Getters */
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
    std::vector< Cell * > getNeighbours() const {return neighbours;}
    
    std::string package() const;
};


#endif 
