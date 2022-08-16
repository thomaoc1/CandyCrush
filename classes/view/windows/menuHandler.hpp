#ifndef MENU_HANDLER_HPP
#define MENU_HANDLER_HPP

#include "../shapes/rectangle.hpp"
#include "../../model/containers/grid.hpp"
#include "../../view/gridDisplay.hpp"
#include "../../control/gridControl.hpp"
#include "mainMenu.hpp"
#include "levelSelection.hpp"
#include "gameMenu.hpp"



class MenuHandler {
    std::shared_ptr<MainMenu> mainMenu = std::make_shared<MainMenu>();
    std::shared_ptr<LevelSelection> levSel = std::make_shared<LevelSelection>();

    std::shared_ptr<Menu> current = mainMenu;
public:
    MenuHandler()=default;
    void draw() const {current->draw();}
    int eventHandler(int event);
};


#endif
