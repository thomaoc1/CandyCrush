#include "mainMenu.hpp"


/**
 * @brief 
 * 
 * @param mouseLoc 
 * @return MenuButtons 
 */
MenuButtons MainMenu::buttonHandler(const Point &mouseLoc) {
    MenuButtons level = MenuButtons::NOTHING;
    if (level1.isClicked(mouseLoc)) level = MenuButtons::LEVEL1;
    else if (level2.isClicked(mouseLoc)) level = MenuButtons::LEVEL2;
    else if (level3.isClicked(mouseLoc)) level = MenuButtons::LEVEL3;    
    else if (resetScore.isClicked(mouseLoc)) {
        FileHandler().resetScore();
        bestscore.setText(score +  "0");
    }
    return level;       
}


/**
 * @brief 
 * 
 */
void MainMenu::draw() {
    Menu::draw();
    title.draw();
    bestscore.draw();

    level1.draw();
    level2.draw();
    level3.draw();

    resetScore.draw();
}


/**
 * @brief 
 * 
 * @param event 
 * @return int 
 */
int MainMenu::eventHandler(int event) {
    MenuButtons state = MenuButtons::NOTHING; 
    switch (event) {
        case FL_PUSH:
            if (Fl::event_button() == FL_LEFT_MOUSE) 
                state = buttonHandler(Point{Fl::event_x(), Fl::event_y()});
            break;
        case FL_KEYDOWN:
            if (Fl::event_key() == FL_Escape) exit(0);
            break;
        default:
            break;
    }
    
    return static_cast<int>(state);
}