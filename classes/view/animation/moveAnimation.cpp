#include "moveAnimation.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Private Methods                                     *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Calculates next translation for movement animation.
 * 
 * @return Point
 *
 */
Point MoveAnimation::currentTranslation() const {
    if (over()) return dest - start;
    double x = (time / getAnimTime()) * (dest.x - start.x);
    double y = (time / getAnimTime()) * (dest.y - start.y);
    return {static_cast<int>(x), static_cast<int>(y)};
}



/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws animation if not complete, then draws shape.
 *
 */
void MoveAnimation::draw() {
    ++time;
    getComponent()->setCenter(start + currentTranslation());
    getComponent()->drawShape();
}