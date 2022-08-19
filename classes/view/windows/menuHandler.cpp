#include "menuHandler.hpp"


int MenuHandler::eventHandler(int event) {
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
