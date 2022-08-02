#include "pulseAnimation.hpp"


void PulseAnimation::draw() {
    ++time;
    int newSize = getComponent()->getSize();
    if (time < animationTime / 2 && static_cast<int>(time) % 2 == 0) --newSize;
    else if (time >= animationTime / 2 && static_cast<int>(time) % 2 == 0) ++newSize;
    if (newSize >= Constants::CANDY_RADIUS) newSize = Constants::CANDY_RADIUS;

    getComponent()->setSize(newSize);
    getComponent()->drawShape();
}