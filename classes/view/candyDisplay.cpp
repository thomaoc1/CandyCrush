#include "candyDisplay.hpp"


void CandyDisplay::draw() {
    if (animation && !animation->over()) animation->draw();
    else drawShape();
}

void CandyDisplay::drawShape() const {
    fl_color(getFLColour());
    fl_begin_polygon();
    fl_circle(getCenter().x, 
                getCenter().y, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}