#include "rectangle.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws shape.
 * 
 */
void Rectangle::draw() const {
    fl_draw_box(type, 
                static_cast<int>(center.x - w / 2),
                static_cast<int>(center.y - h / 2), 
                w,
                h, 
                colour);
}