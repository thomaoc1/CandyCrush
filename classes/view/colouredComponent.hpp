#ifndef COLOURED_COMPONENT_HPP
#define COLOURED_COMPONENT_HPP

#include "componentDisplay.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class ColouredComponent : public ComponentDisplay {
protected:
    Fl_Color colour;
public:
    ColouredComponent(int colour);
};

#endif