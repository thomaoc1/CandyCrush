#ifndef LEVEL_SELECTION_HPP
#define LEVEL_SELECTION_HPP

#include "menu.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class LevelSelection : public Menu {
public:
    void draw() override {Menu::draw();}
    int eventHandler(int event) override {Constants::LEVEL2;}
};

#endif