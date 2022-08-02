#include "pulseAnimation.hpp"


int PulseAnimation::currentPulse(int currentSize) const {
    int newSize = currentSize;
    if (time < animationTime / 2 && static_cast<int>(time) % 2 == 0) --newSize;
    else if (time >= animationTime / 2 && static_cast<int>(time) % 2 == 0) ++newSize;
    if (newSize >= Constants::CANDY_RADIUS) newSize = Constants::CANDY_RADIUS;
    return newSize;
}


void PulseAnimation::draw() {
    ++time;
    int newSize = currentPulse(getComponent()->getSize());

    getComponent()->setSize(newSize);
    getComponent()->drawShape();
}