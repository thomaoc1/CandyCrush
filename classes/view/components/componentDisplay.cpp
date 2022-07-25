#include "componentDisplay.hpp"
#include "../animation/moveAnimation.hpp"
#include "../animation/popAnimation.hpp"
#include "../animation/fillAnimation.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


ComponentDisplay::ComponentDisplay(Point center, int size, int colour) : center{center}, size{size} {
    colour = Constants::associatedColour(colour);
    switch(colour) {
        case Constants::RED:
            fl_colour = FL_RED;
            break;        
        case Constants::BLUE:
            fl_colour = FL_BLUE;
            break;
        case Constants::GREEN:
            fl_colour = FL_GREEN;
            break;
        case Constants::PURPLE:
            fl_colour = FL_MAGENTA;
            break;
        case Constants::YELLOW:
            fl_colour = FL_YELLOW;
            break;
        case Constants::ORANGE:
            fl_colour = fl_rgb_color(255,165,0);
            break;
    }
}


/**
 * @brief Displays the component
 * 
 */
void ComponentDisplay::draw() {
    if (inAnimation()) animation->draw();
    else drawShape();
}


bool ComponentDisplay::inAnimation() const {return animation && !animation->over();} 


/**
 * @brief Starts fill animation
 *
 */
void ComponentDisplay::fillAnimate() {
    if (!inAnimation()) animation = std::make_shared<FillAnimation>(this);
}


/**
 * @brief Starts move animation
 *
 */
void ComponentDisplay::moveAnimate(const Point &dest) {
    if (!inAnimation()) animation = std::make_shared<MoveAnimation>(this, getCenter(), dest);
}


/**
 * @brief Starts swap animation
 *
 */
void ComponentDisplay::swapAnimate(std::shared_ptr<ComponentDisplay>  other) {
    moveAnimate(other->getCenter());
    other->moveAnimate(getCenter());
}


/**
 * @brief Starts pop animation
 *
 */
void ComponentDisplay::popAnimate() {
    if (!inAnimation()) animation = std::make_shared<PopAnimation>(this);
}