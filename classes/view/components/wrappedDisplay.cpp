#include "wrappedDisplay.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Draws associated shape to the window
 * 
 */
void WrappedDisplay::drawShape() const {
    ComponentDisplay::drawShape();

    std::string s = "Wr";
    fl_color(FL_BLACK);
    fl_font(FL_HELVETICA, getSize() / 1.5);
    int width, height;
    fl_measure(s.c_str(), width, height, false);
    fl_draw(s.c_str(), getCenter().x-width/2, getCenter().y-fl_descent()+height/2);
}


