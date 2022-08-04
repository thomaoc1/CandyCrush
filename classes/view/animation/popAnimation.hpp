/**
 * File : 
 *  popAnimation.hpp
 *
 * Decription :
 *  Class reponsible for animating a popping / suppression event 
 * 
 * Dependencies : 
 *  animation.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */


#ifndef POP_ANIMATION_HPP
#define POP_ANIMATION_HPP

#include "animation.hpp"

class PopAnimation : public Animation {
    const double normalSize;
public:
    PopAnimation(ComponentDisplay * component) : Animation{component}, normalSize{component->getSize()} {}
    void draw() override;
};

#endif