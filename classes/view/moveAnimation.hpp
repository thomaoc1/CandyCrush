#ifndef MOVE_ANIMATION_HPP
#define MOVE_ANIMATION_HPP

#include "../model/point.hpp"
#include "animation.hpp"
#include "componentDisplay.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <iostream>
class MoveAnimation  : public Animation {
    Point start;
    Point dest;
public:
    MoveAnimation(ComponentDisplay * component, const Point &start, const Point &dest) : Animation{component}, start{start}, dest{dest} {}
    // ~MoveAnimation() {std::cout << "dead" << std::endl;}
    void draw() override;
    Point finalLoc() const override {return dest;}
private:
    Point currentTranslation() const;
};

#endif