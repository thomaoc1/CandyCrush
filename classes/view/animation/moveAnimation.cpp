#include "moveAnimation.hpp"

#include <iostream>


Point MoveAnimation::currentTranslation() const {
    if (over()) return dest - start;
    double x = (time / animationTime) * (dest.x - start.x);
    double y = (time / animationTime) * (dest.y - start.y);
    return {static_cast<int>(x), static_cast<int>(y)};
}


void MoveAnimation::draw() {
    ++time;
    getComponent()->setCenter(start + currentTranslation());
    getComponent()->drawShape();
}