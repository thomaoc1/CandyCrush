#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include "menu.hpp"
#include "../common/background.hpp"
#include "../shapes/rectangle.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MainMenu : public Menu {
    // Rectangle button{};
public:
    void draw() override;
    int eventHandler(int event) override {std::cout << "MAIN MENU" << std::endl; if(event == FL_PUSH) return Constants::LEVEL2; else return -1;}
};

#endif