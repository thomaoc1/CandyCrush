#include "wrappedDisplay.hpp"


void WrappedDisplay::drawShape() const {
    fl_color(fl_colour);
    fl_begin_polygon();
    fl_circle(getCenter().x, 
                getCenter().y, 
                size);
    fl_end_polygon();
}


