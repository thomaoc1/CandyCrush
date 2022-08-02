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
    const double animationTime = 20;
protected:
    double time = 0;
public:
    Animation(ComponentDisplay * component) : component{component} {}

    virtual void draw()=0;
    virtual ComponentDisplay * getComponent() {return component;}
    virtual int getAnimTime() const {return animationTime;}
    virtual bool over() const {return time >= animationTime;}
    
    virtual int type() const {return Constants::CANT_IGNORE;}
};

#endif
