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
                static_cast<int>(center.x - Constants::CELL_SIZE/2),
                static_cast<int>(center.y - Constants::CELL_SIZE/2), 
                size,
                size, 
                colour);
}