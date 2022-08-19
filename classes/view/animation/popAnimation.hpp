/**
 * @file popAnimation.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of the graphical representation 
 *  of a popping animation.
 * 
 * @version 0.1
 * @date 2022-08-19
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