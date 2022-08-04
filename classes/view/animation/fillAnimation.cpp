#include "fillAnimation.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Private Methods                                     *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Calculates next size for the fill animation
 * 
 * @param size
 * 
 * @return int
 * 
 */
int FillAnimation::nextSize(int size) const {
    int newSize = 0;
    if (time != 1) {
        newSize = size + 4;
        if (newSize >= normalSize) newSize = normalSize;
    } 
    return newSize;
}


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Displays next phase of Fill animation 
 *
 */
void FillAnimation::draw() {
    ++time;
    int newSize = nextSize(getComponent()->getSize());
    if (newSize == normalSize) time = getAnimTime();
    getComponent()->setSize(newSize); 
    getComponent()->drawShape();
}