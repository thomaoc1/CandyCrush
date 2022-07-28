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
    fl_circle(static_cast<double>(center.x), 
                static_cast<double>(center.y), 
                static_cast<double>(size));
    fl_end_polygon();
}