/**
 * File : 
 *  animation.hpp
 *
 * Decription :
 *  Abstract class which generalises Animations
 * 
 * Dependencies : 
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */


#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class ComponentDisplay;

#include "../components/componentDisplay.hpp"
#include <memory>

class Animation {
    ComponentDisplay * component;
protected:
    const double animationTime = 30;
    double time = 0;
public:
    Animation(ComponentDisplay * component) : component{component} {}
    virtual void draw()=0;
    virtual ComponentDisplay * getComponent() {return component;}
    virtual bool over() const {return time >= animationTime;}
};

#endif
