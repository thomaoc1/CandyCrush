/**
 * @file gridControl.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which makes changes on to the model
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef GRIDCONTROL_HPP
#define GRIDCONTROL_HPP

#include "../model/containers/grid.hpp"

#include <FL/Fl.H>
#include <string>

class GridControl {
    std::shared_ptr<Grid> grid;
    const GridDisplay &view;
    Point click, clickToIndex;
    Point hold, holdToIndex;
    bool dragged = false;

public:
    GridControl(std::shared_ptr<Grid> grid, const GridDisplay &view) : grid{grid}, view{view} {} 
    int proccessEvent(const int event);
private:
    bool gameOver() const {return grid->gameState() == GameState::LOST || grid->gameState() == GameState::WON;}
    bool inAnimation() const {return view.inAnimation();}
    void clickEvent(const Point &mouseLoc);
    bool coordInGame(const Point &mouseLoc) const;
    Point coordToCell(const Point &mouseLoc) const;
    void dragEvent(const Point &mouseLoc);
};


#endif