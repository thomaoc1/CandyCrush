#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation;

#include "colouredComponent.hpp"
#include <memory>

class Animation {
    ColouredComponent * component;
protected:
    const double animationTime = 60;
    double time = 0;
public:
    Animation(ColouredComponent * component) : component{component} {}
    virtual void draw()=0;
    virtual ColouredComponent * getComponent() {return component;}
    virtual bool over() const {return time >= animationTime;}
};

#endif
