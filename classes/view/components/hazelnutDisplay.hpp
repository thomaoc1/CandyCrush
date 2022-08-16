#ifndef HAZELNUT_DISPLAY_HPP
#define HAZELNUT_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/hazelShape.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class HazelnutDisplay : public ComponentDisplay {
public:
    HazelnutDisplay(const Point &center) : 
        ComponentDisplay(std::make_shared<HazelShape>(center, Constants::CANDY_RADIUS)) {}
    HazelnutDisplay(const HazelnutDisplay &) = default;
    HazelnutDisplay(HazelnutDisplay &&) = default;
};

#endif