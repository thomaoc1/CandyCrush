/**
 * File : 
 *  fillAnimation.hpp
 *
 * Decription :
 *  Class reponsible for animating a filling event 
 * 
 * Dependencies : 
 *  animation.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
 * 
 */

#ifndef FILL_ANIMATION_HPP
#define FILL_ANIMATION_HPP

#include "animation.hpp"

class FillAnimation : public Animation {
    Fl_Color fl_colour;
    const double normalSize;
public:
    FillAnimation(ComponentDisplay * component) : Animation{component}, normalSize{component->getSize()} {}
    void draw();
private:
    int nextSize(int size) const;
};


#endif