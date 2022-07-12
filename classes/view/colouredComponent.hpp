#ifndef COLOURED_COMPONENT_HPP
#define COLOURED_COMPONENT_HPP

class ColouredComponent;

#include "componentDisplay.hpp"
#include "animation.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class ColouredComponent : public ComponentDisplay {
    Fl_Color fl_colour;
public:
    ColouredComponent(Point center, int colour);
    virtual Fl_Color getFLColour() const {return fl_colour;} 
};

#endif