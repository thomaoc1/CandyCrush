#include "bombDisplay.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws associated shape to the window
 * 
 */
void BombDisplay::drawShape() const {
    ComponentDisplay::drawShape();
    text.draw();
}


/**
 * \see ComponentDisplay::setCenter(const Point &)
 */
void BombDisplay::setCenter(const Point &dest) {
    shape->setCenter(dest);
    text.setCenter(dest);
}


void BombDisplay::setSize(double newSize) {
    shape->setSize(newSize);
    text.setSize(static_cast<int>(newSize / 1.5));
}
