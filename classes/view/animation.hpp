#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation;

#include "colouredComponent.hpp"

class Animation {
    ColouredComponent * component;
    const int animationTime = 15;
    int time = 0;
public:
    Animation(ColouredComponent * component) : component{component} {}
    virtual void draw()=0;
    virtual bool animationOver() const {return time >= animationTime;}
    virtual void incrementTime() {++time;}
};

#endif
