#include "frostingDisplay.hpp"


void FrostingDisplay::drawShape() const {
    ComponentDisplay::drawShape();
    text.draw();
}