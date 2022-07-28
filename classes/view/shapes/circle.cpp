#include "circle.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws shape.
 * 
 */
void Circle::draw() const {
    fl_color(colour);
    fl_begin_polygon();
    fl_circle(center.x, 
                center.y, 
                radius);
    fl_end_polygon();
}