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

#include "../components/gameComponent.hpp"
#include "../../shared/point.hpp"

#include <memory>

class Cell {
    const int row, col;
    std::shared_ptr<GameComponent> occupied;
    std::vector< Cell * > vertNbs;
    std::vector< Cell * > horizNbs;
    std::vector< Cell * > belowNbs{nullptr, nullptr, nullptr};
    bool toPop = false;
public:
    Cell(int row, int col) : row{row}, col{col} {}

    /* Setters */
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    void unOccupy() {setOccupied(nullptr);}
    void setVertNbs(const std::vector< Cell * > &nbs) {vertNbs = nbs;}
    void setHorizNbs(const std::vector< Cell * > &nbs) {horizNbs = nbs;}
    void setBelow(Cell * cell) {belowNbs[Constants::BELOW] = cell;}
    void setBelowLeft(Cell * cell) {belowNbs[Constants::BELOW_LEFT] = cell;}
    void setBelowRight(Cell * cell) {belowNbs[Constants::BELOW_RIGHT] = cell;}
    void willPop() {toPop = true;}
    void popped() {toPop = false;}
    
    /* Getters */
    Point getLocation() const {return Point{col, row};}
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
    std::vector< Cell * > getVertNbs() const {return vertNbs;}
    std::vector< Cell * > getHorizNbs() const {return horizNbs;}
    Cell * getBelow(int direction) const {return belowNbs[direction];}
    bool getPop() const {return toPop;}
    
    int getColour() const {return occupied ? occupied->getColour() : Constants::NONE;}
    int type() const {return occupied ? occupied->type() : Constants::EMPTY;};
};


#endif 
