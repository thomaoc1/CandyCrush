#include "pulseAnimation.hpp"


void PulseAnimation::draw() {
    ++time;
    int newSize = getComponent()->getSize();
    if (time < animationTime / 2) newSize *= 0.98;
    else {
        if (newSize >= Constants::CANDY_RADIUS) newSize = Constants::CANDY_RADIUS;
        else newSize *= 1.02;
    }
    if (newSize >= Constants::CANDY_RADIUS / 2 || time >= animationTime  / 2) getComponent()->setSize(newSize);
    else time = animationTime / 2;

    getComponent()->drawShape();
}