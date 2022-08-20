#include "menuHandler.hpp"


/**
 * @brief Displays title screen or current menu depending
 *  on time
 * 
 */
void MenuHandler::draw() {
    if (time > 0) {
        --time;
        ts.draw();
    }
    else current->draw();
}


/**
 * @brief Forwards event to correct menu.
 * 
 * @param event 
 * @return int 
 */
int MenuHandler::eventHandler(int event) {
    if (time > 0) return -1;
    MenuButtons button = static_cast<MenuButtons>(current->eventHandler(event));
    switch (button) {
        case MenuButtons::BACK:
            current = &mainMenu;
            mainMenu.recheckScore();
            break;
        case MenuButtons::LEVEL1:
        case MenuButtons::LEVEL2:
        case MenuButtons::LEVEL3:
            game.setLevel(button);
            current = &game;
            break;
        default:
            break;
    }
    return event;
}


