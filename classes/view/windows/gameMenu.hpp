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
    GameMenu()
        : gridDisplay{GridDisplay()}, 
          grid{std::make_shared<Grid>(gridDisplay)}, 
          gridControl{std::make_shared<GridControl>(grid, gridDisplay)} {;}

    ~GameMenu() {}

    void draw() override {gridDisplay.draw();}
    int eventHandler(int event) override {return gridControl->proccessEvent(event);}
    bool inAnimation() const override {return gridDisplay.inAnimation();}
    void setLevel(int level) {grid->setLevel(associatedFile(level));} 
private:
    std::string associatedFile(int level) const;
};

#endif