#ifndef MENU_DISPLAY_HPP
#define MENU_DISPLAY_HPP

#include "../shapes/rectangle.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MenuDisplay {
    bool over = false;
public:



    bool over() const;
    void draw() const;
};

#endif