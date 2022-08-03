#include "hazelShape.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws shape.
 * 
 */
void HazelShape::draw() const {
    
    fl_draw_box(FL_OFLAT_BOX, static_cast<int>(center.x - (size*1.5)/2),
                static_cast<int>(center.y - size),
                 size*1.5, size*2, colour);
}