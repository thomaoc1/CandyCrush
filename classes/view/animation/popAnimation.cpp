#include "popAnimation.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws animation if not complete, then draws shape.
 * 
 */
void PopAnimation::draw() {
    ++time;
    int newSize = getComponent()->getSize() - 2;
    if (newSize > 0) getComponent()->setSize(newSize);
    else {
        getComponent()->setSize(0);
        time = animationTime;
    }
    getComponent()->drawShape();
}