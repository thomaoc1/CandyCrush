#include "menuHandler.hpp"


int MenuHandler::eventHandler(int event) {
    int button = current->eventHandler(event);
    switch (button) {
        case Constants::BACK:
            current = &mainMenu;
            mainMenu.recheckScore();
            break;
        case Constants::GAME_OVER:
            gameOver = true;
            break;
        case Constants::LEVEL1:
        case Constants::LEVEL2:
        case Constants::LEVEL3:
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