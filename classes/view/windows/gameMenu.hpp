/**
 * @file gameMenu.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation the game.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include "menu.hpp"
#include "../../model/containers/grid.hpp"
#include "../../view/gridDisplay.hpp"
#include "../../control/gridControl.hpp"

class GameMenu : public Menu {
    GridDisplay gridDisplay;
    Grid grid;
    GridControl gridControl;
public:
    GameMenu()
        : gridDisplay{GridDisplay()}, 
          grid{Grid(gridDisplay)}, 
          gridControl{GridControl(grid, gridDisplay)} {}

    ~GameMenu() {}

    void draw() override {bg.draw(); gridDisplay.draw();}
    int eventHandler(int event) override {return gridControl.proccessEvent(event);}
    void setLevel(MenuButtons level) {grid.setLevel(associatedFile(level));} 
private:
    std::string associatedFile(MenuButtons level) const;
};

#endif