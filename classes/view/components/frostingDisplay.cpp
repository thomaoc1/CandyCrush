#include "frostingDisplay.hpp"


/**
 * @brief Draws associated shape.
 * 
 */
void FrostingDisplay::drawShape() const {
    ComponentDisplay::drawShape();
    text.draw();
}


/**
 * @brief Setter for the size.
 * 
 * @param newSize 
 */
void FrostingDisplay::setSize(double newSize) {
    shape->setSize(newSize);
    text.setSize(static_cast<int>(newSize / 1.5));
}