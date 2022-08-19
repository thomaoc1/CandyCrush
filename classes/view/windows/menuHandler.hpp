/**
 * @file menuHandler.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for deciding which Menu to display.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef MENU_HANDLER_HPP
#define MENU_HANDLER_HPP

#include "../shapes/rectangle.hpp"
#include "../../model/containers/grid.hpp"
#include "../../view/gridDisplay.hpp"
#include "../../control/gridControl.hpp"
#include "mainMenu.hpp"
#include "gameMenu.hpp"

class MenuHandler {
    MainMenu mainMenu;
    GameMenu game;

    Menu * current = &mainMenu;

    bool gameOver = false;
public:
    MenuHandler() = default;
    void draw() {current->draw();}
    int eventHandler(int event);
};


#endif
