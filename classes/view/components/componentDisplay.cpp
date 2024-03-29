#include "componentDisplay.hpp"
#include "../animation/moveAnimation.hpp"
#include "../animation/popAnimation.hpp"
#include "../animation/fillAnimation.hpp"
#include "../animation/pulseAnimation.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Displays the component
 * 
 */
void ComponentDisplay::draw() {
    if (inAnimation()) animation->draw();
    else drawShape();
}


/**
 * @brief Displays the component
 * 
 */
void ComponentDisplay::drawShape() const {
    shape->draw();
}


bool ComponentDisplay::inAnimation() const {return animation && !animation->over();} 
                                                    

/**
 * @brief Starts fill animation
 *
 */
void ComponentDisplay::fillAnimate() {
    animation = std::make_shared<FillAnimation>(this);
}


/**
 * @brief Starts move animation
 *
 */
void ComponentDisplay::moveAnimate(const Point &dest) {
    animation = std::make_shared<MoveAnimation>(this, getCenter(), dest);
}


/**
 * @brief Starts swap animation
 *
 */
void ComponentDisplay::swapAnimate(std::shared_ptr<ComponentDisplay>  other) {
    moveAnimate(other->getCenter());
    other->moveAnimate(getCenter());
}


void ComponentDisplay::suggAnimate() {
    animation = std::make_shared<PulseAnimation>(this);
}


/**
 * @brief Starts pop animation
 *
 */
void ComponentDisplay::popAnimate() {
    popping = true;
    animation = std::make_shared<PopAnimation>(this);
}


/**
 * @brief Returns the priority level of the animation.
 * 
 * @return AnimPriority 
 */
AnimPriority ComponentDisplay::animationType() const {return animation->type();}