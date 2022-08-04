#include "frostingDisplay.hpp"


void FrostingDisplay::drawShape() const {
    ComponentDisplay::drawShape();
    text.draw();
}


void FrostingDisplay::setSize(double newSize) {
    shape->setSize(newSize);
    text.setSize(static_cast<int>(newSize / 1.5));
}