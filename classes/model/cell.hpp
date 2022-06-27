#ifndef CELL_HPP
#define CELL_HPP

#include "gameComponent.hpp"

#include <memory>

class Cell {
    std::shared_ptr<GameComponent> occupied;
public:
    Cell(const std::shared_ptr<GameComponent> &gc) : occupied{gc} {}
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
};


#endif 
