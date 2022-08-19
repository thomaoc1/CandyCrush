/**
 * @file animation.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Abstract class which generalises the representation of an animation.
 * 
 * @version 0.1
 * @date 2022-08-19
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
    
    virtual AnimPriority type() const {return AnimPriority::CANT_IGNORE;}
};

#endif
