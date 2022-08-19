/**
 * @file pulseAnimation.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of the graphical representation 
 *  of a pulse animation.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef PULE_ANIMATION_HPP
#define PULE_ANIMATION_HPP

#include "animation.hpp"

#include <math.h>

class PulseAnimation : public Animation {
    int animationTime = 30;
public:
    PulseAnimation(ComponentDisplay * component) : Animation{component} {}
    ~PulseAnimation() {getComponent()->setSize(Constants::CANDY_RADIUS);}
    void draw() override;
    int getAnimTime() const {return animationTime;}
    bool over() const {return time >= animationTime;}
    AnimPriority type() const override {return AnimPriority::IGNORE;}
private:
    int currentPulse(int currentSize) const;
};

#endif