#include "popAnimation.hpp"

void PopAnimation::draw() {
    ++time;
    int newSize = getComponent()->getSize() - 1;
    if (newSize > 0) getComponent()->setSize(newSize);
    else {
        getComponent()->setSize(0);
        time = animationTime;
    }
    getComponent()->drawShape();
}