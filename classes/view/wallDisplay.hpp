#ifndef WALL_DISPLAY_HPP
#define WALL_DISPLAY_HPP

#include "componentDisplay.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class WallDisplay : public ComponentDisplay {
    const Fl_Color fillColour = FL_BLACK;
public:
    void draw(int y, int x) const override;
};

#endif