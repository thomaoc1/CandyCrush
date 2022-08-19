/**
 * @file cell.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which represents a 'slot' in the grid
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef CELL_HPP
#define CELL_HPP

#include "../components/gameComponent.hpp"
#include "../../common/point.hpp"

#include <memory>

class Cell {
    const int row, col;
    std::shared_ptr<GameComponent> occupied;
    std::vector< Cell * > nbs;
    std::vector< Cell * > vertNbs;
    std::vector< Cell * > horizNbs;
    std::vector< Cell * > crossNbs;
    std::vector< Cell * > belowNbs{nullptr, nullptr, nullptr};
    std::vector< Cell * > aboveNbs{nullptr, nullptr, nullptr};
    bool toPop = false;

public:
    Cell(int row, int col) noexcept : row{row}, col{col} {}
    Cell(const Cell &) = default;
    Cell(Cell &&) = default;

    /* Setters */
    void setOccupied(const std::shared_ptr<GameComponent> &gc) {occupied = gc;}
    void unOccupy() {setOccupied(nullptr);}
    void setNbs(const std::vector< Cell * > &nbs);
    void willPop() {toPop = true;}
    void popped() {toPop = false;}
    
    /* Getters */
    Point getLocation() const {return Point{col, row};}
    std::shared_ptr<GameComponent> getOccupied() const {return occupied;}
    std::vector< Cell * > getVertNbs() const {return vertNbs;}
    std::vector< Cell * > getHorizNbs() const {return horizNbs;}
    std::vector< Cell * > getCrossNbs() const {return crossNbs;}
    Cell * getBelow(Beneath direction) const {return belowNbs[static_cast<int>(direction)];}
    std::vector< Cell * > getNbs() const {return nbs;}
    bool getPop() const {return toPop;}
    Colour getColour() const {return occupied ? occupied->getColour() : Colour::NONE;}
    ComponentType component() const {return occupied->type();}
    Component type() const {return occupied->type().type;}
    ComponentState compState() const {return occupied->pop();}
};


#endif 
