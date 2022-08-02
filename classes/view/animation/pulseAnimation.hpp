#ifndef PULE_ANIMATION_HPP
#define PULE_ANIMATION_HPP

#include "animation.hpp"

#include <math.h>

class PulseAnimation : public Animation {
    int animationTime = 30;
public:
    PulseAnimation(ComponentDisplay * component) : Animation{component} {}
    void draw() override;
    int getAnimTime() const {return animationTime;}
    bool over() const {return time >= animationTime;}
    int type() const override {return Constants::IGNORE;}
private:
    int currentPulse() const;
};

#endif