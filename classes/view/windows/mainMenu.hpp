#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "menu.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainMenu : public Menu {
public:
    void draw() override;
    int eventHandler(int event) override;
};

#endif