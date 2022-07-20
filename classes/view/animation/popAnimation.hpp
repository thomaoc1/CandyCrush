#ifndef POP_ANIMATION_HPP
#define POP_ANIMATION_HPP

#include "animation.hpp"

class PopAnimation : public Animation {
public:
    PopAnimation(ComponentDisplay * component) : Animation{component} {}
    void draw() override;
};

#endif