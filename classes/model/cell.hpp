/**
 * File : 
 *  cell.hpp
 *
 * Decription :
 *  Class which represents a possible 'slot' in which a GameComponent can be in
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 */

#ifndef CELL_HPP
#define CELL_HPP

#include "gameComponent.hpp"

#include <memory>

class Cell {
    std::shared_ptr<GameComponent> occupied;
    std::vector< Cell * > vertNbs;
    std::vector< Cell * > horizNbs;
public:
    /* Setters */
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    void setVertNbs(const std::vector< Cell * > &nbs) {vertNbs = nbs;}
    void setHorizNbs(const std::vector< Cell * > &nbs) {horizNbs = nbs;}
    
    /* Getters */
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
    std::vector< Cell * > getVertNbs() const {return vertNbs;}
    std::vector< Cell * > getHorizNbs() const {return horizNbs;}
    
    std::string package() const;
};


#endif 
