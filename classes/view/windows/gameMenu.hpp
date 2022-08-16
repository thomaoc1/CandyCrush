#ifndef GAME_MENU_HPP
#define GAME_MENU_HPP

#include "menu.hpp"
#include "../../model/containers/grid.hpp"
#include "../../view/gridDisplay.hpp"
#include "../../control/gridControl.hpp"

class GameMenu : public Menu {
    GridDisplay gridDisplay;
    std::shared_ptr<Grid> grid;
    std::shared_ptr<GridControl> gridControl;
public:
    GameMenu(int level)
        : gridDisplay{GridDisplay()}, 
          grid{std::make_shared<Grid>(gridDisplay, associatedFile(level))}, 
          gridControl{std::make_shared<GridControl>(grid, gridDisplay)} {std::cout << associatedFile(level) << std::endl;}

    ~GameMenu() {std::cout << "Death of GameMenu" << std::endl;}

    void draw() override {gridDisplay.draw();}
    int eventHandler(int event) override {return gridControl->proccessEvent(event);}
private:
    std::string associatedFile(int level) const;
};

#endif