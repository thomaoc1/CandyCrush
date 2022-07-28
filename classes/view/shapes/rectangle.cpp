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
    fl_draw_box(FL_FLAT_BOX, 
                static_cast<int>(center.x - Constants::INTER_CELL/2),
                static_cast<int>(center.y - Constants::INTER_CELL/2), 
                size,
                size, 
                colour);
}