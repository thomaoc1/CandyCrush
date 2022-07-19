#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class ComponentDisplay;

#include "componentDisplay.hpp"
#include <memory>

class Animation {
    ComponentDisplay * component;
protected:
    const double animationTime = 60;
    double time = 0;
public:
    Animation(ComponentDisplay * component) : component{component} {}
    virtual void draw()=0;
    virtual Point finalLoc() const=0;
    virtual ComponentDisplay * getComponent() {return component;}
    virtual bool over() const {return time >= animationTime;}
};

#endif