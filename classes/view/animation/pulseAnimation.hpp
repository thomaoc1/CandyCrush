#ifndef PULE_ANIMATION_HPP
#define PULE_ANIMATION_HPP

#include "animation.hpp"

class PulseAnimation : public Animation {
public:
    PulseAnimation(ComponentDisplay * component) : Animation{component} {}
    void draw() override;
private:
    int currentPulse() const;
};

#endif