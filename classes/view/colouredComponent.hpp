#ifndef COLOURED_COMPONENT_HPP
#define COLOURED_COMPONENT_HPP

#include "componentDisplay.hpp"
#include <iostream>

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class ColouredComponent : public ComponentDisplay {
protected:
    Fl_Color fl_colour;
public:
    ColouredComponent(Point center, int colour);
};

#endif