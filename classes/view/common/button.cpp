#include "button.hpp"


bool Button::inButton(const Point &mouseLoc) const {
    return mouseLoc.x >= r.getCenter().x - r.getWidth() / 2 
            && mouseLoc.x <= r.getCenter().x + r.getWidth() / 2 
            && mouseLoc.y >= r.getCenter().y - r.getHeight() / 2
            && mouseLoc.y <= r.getCenter().y + r.getHeight() / 2;
}


void Button::draw() const {
    r.draw();
    text.draw(0, 55);
}