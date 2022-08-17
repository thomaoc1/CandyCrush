#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "menu.hpp"
#include "../common/background.hpp"
#include "../common/button.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainMenu : public Menu {
    Button level1;
    Button level2;
    Button level3;

    Text title{Point{400, 150}, "CandySmash", FL_HELVETICA, 50};
public:
    MainMenu() 
        : Menu(), 
            level1{Point{400, 300}, "Candy Smash", FL_BLACK, 400, 100}, 
            level2{Point{400, 400}, "Ingredient Smash", FL_BLACK, 400, 100}, 
            level3{Point{400, 500}, "Frosting Break", FL_BLACK, 400, 100} {}

    void draw() override;
    int eventHandler(int event) override;

private:
    int buttonHandler(const Point &mouseLoc) const;
};


#endif