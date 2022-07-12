#ifndef MOVE_ANIMATION_HPP
#define MOVE_ANIMATION_HPP

#include "../model/point.hpp"
#include "animation.hpp"
#include "colouredComponent.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class MoveAnimation  : public Animation {
    Point dest;
public:
    MoveAnimation(ColouredComponent * component, const Point &dest) : Animation{component}, dest{dest} {}
    void draw() override;
private:
    Point currentTranslation(const Point &dest);
};

#endif