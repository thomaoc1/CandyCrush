#include "button.hpp"


/**
 * @brief Checks if the mouse location is in the button
 * 
 * @param mouseLoc 
 * @return true 
 * @return false 
 */
bool Button::inButton(const Point &mouseLoc) const {
    return mouseLoc.x >= r.getCenter().x - r.getWidth() / 2 
            && mouseLoc.x <= r.getCenter().x + r.getWidth() / 2 
            && mouseLoc.y >= r.getCenter().y - r.getHeight() / 2
            && mouseLoc.y <= r.getCenter().y + r.getHeight() / 2;
}


/**
 * @brief Draws the button.
 * 
 */
void Button::draw() const {
    r.draw();
    text.draw(0, 55);
}