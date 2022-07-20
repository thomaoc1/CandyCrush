#ifndef FILL_ANIMATION_HPP
#define FILL_ANIMATION_HPP

#include "animation.hpp"

class FillAnimation : public Animation {
    Fl_Color fl_colour;
public:
    FillAnimation(ComponentDisplay * component) : Animation{component} {}
    void draw();
};


#endif