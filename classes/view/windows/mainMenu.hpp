#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "menu.hpp"
#include "../common/background.hpp"
#include "../common/button.hpp"
#include "../../model/filehandler/fileHandler.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainMenu : public Menu {
    Button level1;
    Button level2;
    Button level3;
    Button resetScore;

    FileHandler fh;

    std::string score = "Best Score : ";
    Text title{Point{400, 150}, "CandySmash", FL_HELVETICA, 50};
    Text bestscore{Point{400, 200}, score + std::to_string(fh.getBestScore()), FL_HELVETICA, 20};
public:
    MainMenu() 
        : Menu(), 
            level1{Point{400, 300}, "Sweet Salvation", FL_BLACK, 400, 100}, 
            level2{Point{400, 400}, "Cherry Chaser", FL_BLACK, 400, 100}, 
            level3{Point{400, 500}, "Frosting Frenzy", FL_BLACK, 400, 100},
            resetScore{Point{400, 650}, "Reset Score", FL_BLACK, 400, 100} {}

    void draw() override;
    int eventHandler(int event) override;
    void recheckScore() {bestscore.setText(score + std::to_string(fh.getBestScore()));}
private:
    MenuButtons buttonHandler(const Point &mouseLoc);
};


#endif