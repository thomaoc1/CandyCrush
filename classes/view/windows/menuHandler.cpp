#include "menuHandler.hpp"


int MenuHandler::eventHandler(int event) {
    int button = current->eventHandler(event);
    switch (button) {
        case Constants::BACK:
            current = &mainMenu;
            break;
        case Constants::GAME_OVER:
            gameOver = true;
            current = &mainMenu;
            break;
        case Constants::LEVEL1:
        case Constants::LEVEL2:
        case Constants::LEVEL3:
            std::cout << "LEVEL" << std::endl;
            game.setLevel(button);
            current = &game;
            break;
    }
    return event;
}


void MenuHandler::draw() {
    // if (gameOver && !current->inAnimation()) 
    //     current = &mainMenu;

    current->draw();
}