#ifndef CANDY_DISPLAY_HPP
#define CANDY_DISPLAY_HPP

#include "colouredComponent.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CandyDisplay : public ColouredComponent {

public:
    CandyDisplay(int colour) : ColouredComponent(colour) {}
    void draw(int y, int x) const override;
};

#endif