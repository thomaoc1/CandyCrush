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
            std::cout << "GAME_OVER" << std::endl;
            current = mainMenu;
            break;
        case Constants::LEVEL1:
        case Constants::LEVEL2:
        case Constants::LEVEL3:
            std::cout << "LEVEL" << std::endl;
            current = std::make_shared<GameMenu>(button);
            break;
    }
    return event;
}