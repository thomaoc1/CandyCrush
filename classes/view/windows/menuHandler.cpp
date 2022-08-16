#include "menuHandler.hpp"


int MenuHandler::eventHandler(int event) {
    int button = current->eventHandler(event);
    switch (button) {
        case Constants::BACK:
            current = mainMenu;
            break;
        case Constants::PLAY:
            current = levSel;
            break;
        case Constants::GAME_OVER:
            current = mainMenu;
            break;
        case Constants::LEVEL1:
        case Constants::LEVEL2:
        case Constants::LEVEL3:
            current = std::make_shared<GameMenu>(button);
            break;
    }
    return event;
}