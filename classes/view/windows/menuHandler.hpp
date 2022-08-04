#ifndef MENU_DISPLAY_HPP
#define MENU_DISPLAY_HPP

#include "../shapes/rectangle.hpp"
#include "../../model/containers/grid.hpp"
#include "../../view/gridDisplay.hpp"
#include "../../control/gridControl.hpp"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class MenuHandler {
    GridDisplay gridDisplay;
    GridControl gridControl{gridDisplay};
public:
    void launchGame(const std::string &filename);
};

#endif