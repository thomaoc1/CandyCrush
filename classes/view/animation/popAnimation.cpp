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
    double newSize = getComponent()->getSize() - 4;
    if (newSize > 0) 
        getComponent()->setSize(newSize);
    
    else {
        getComponent()->setSize(0);
        time = getAnimTime();
    }

    // if (time == getAnimTime()) getComponent()->setSize(0);
    
    getComponent()->drawShape();
}