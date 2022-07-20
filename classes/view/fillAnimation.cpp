#include "fillAnimation.hpp"

void FillAnimation::draw() {
    ++time;
    if (time == 1) {
        getComponent()->setSize(0);
        return;
    }
    int newSize = getComponent()->getSize() + 1;
    if (newSize >= Constants::CANDY_RADIUS) {
        getComponent()->setSize(Constants::CANDY_RADIUS);
        time = animationTime;
    }
    else getComponent()->setSize(newSize); 
}