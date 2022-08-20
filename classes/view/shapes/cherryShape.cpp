#include "cherryShape.hpp"


/**
 * @brief Draws shape.
 * 
 */
void CherryShape::draw() const {
    fl_color(colour);
    fl_begin_polygon();
    fl_circle(static_cast<double>(center.x + Constants::CELL_SIZE/5), 
                static_cast<double>(center.y + 10), 
                static_cast<double>(size/2));
    fl_circle(static_cast<double>(center.x - Constants::CELL_SIZE/5), 
                static_cast<double>(center.y + 10), 
                static_cast<double>(size/2));
    fl_end_polygon();
}