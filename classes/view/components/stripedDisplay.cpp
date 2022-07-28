#include "stripedDisplay.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws associated shape to the window
 * 
 */
void StripedDisplay::drawShape() const {
    ComponentDisplay::drawShape();
    text.draw();
}


void StripedDisplay::setCenter(const Point &dest) {
    shape->setCenter(dest);
    text.setCenter(dest);
}


void StripedDisplay::setSize(int newSize) {
    shape->setSize(newSize);
    text.setSize(static_cast<int>(newSize / 1.5));
}
