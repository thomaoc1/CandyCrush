#include "wrappedDisplay.hpp"


void WrappedDisplay::drawShape() const {
    fl_color(getFLColour());
    fl_begin_polygon();
    fl_circle(getCenter().x, 
                getCenter().y, 
                Constants::CANDY_RADIUS);
    fl_end_polygon();
}


void WrappedDisplay::draw() {
    if (animation) animation->draw();
    else drawShape();
}