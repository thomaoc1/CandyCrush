#include "mainMenu.hpp"


int MainMenu::buttonHandler(const Point &mouseLoc) const {
    int level = Constants::NOTHING;
    if (level1.isClicked(mouseLoc)) level = Constants::LEVEL1;
    else if (level2.isClicked(mouseLoc)) level = Constants::LEVEL2;
    else if (level3.isClicked(mouseLoc)) level = Constants::LEVEL3;    

    return level;       
}


void MainMenu::draw() {
    Menu::draw();
    title.draw();

    level1.draw();
    level2.draw();
    level3.draw();
}


int MainMenu::eventHandler(int event) {
    int state = Constants::NOTHING; 
    switch (event) {
        case FL_PUSH:
            if (Fl::event_button() == FL_LEFT_MOUSE) 
                state = buttonHandler(Point{Fl::event_x(), Fl::event_y()});
            break;
        case FL_KEYDOWN:
            if (Fl::event_key() == FL_Escape) exit(0);
            break;
    }
    
    return state;
}