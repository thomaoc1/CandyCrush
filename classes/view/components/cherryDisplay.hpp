#ifndef CHERRY_DISPLAY_HPP
#define CHERRY_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/cherryShape.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CherryDisplay : public ComponentDisplay {
public:
    CherryDisplay(const Point &center) : ComponentDisplay{std::make_shared<CherryShape>(center, FL_RED, Constants::CANDY_RADIUS)} {}
    CherryDisplay(const CherryDisplay &) = default;
    CherryDisplay(CherryDisplay &&) = default;

    // DEBUG
    std::string type() const override {return "C";}
};

#endif