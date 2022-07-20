#include "componentDisplay.hpp"
#include "animation/moveAnimation.hpp"
#include "animation/popAnimation.hpp"
#include "animation/fillAnimation.hpp"

ComponentDisplay::ComponentDisplay(Point center, int size, int colour) : center{center}, size{size} {
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


void ComponentDisplay::draw() {
    if (inAnimation()) animation->draw();
    else drawShape();
}


bool ComponentDisplay::inAnimation() const {return animation && !animation->over();} 


void ComponentDisplay::fillAnimate() {
    if (!inAnimation()) animation = std::make_shared<FillAnimation>(this);
}


void ComponentDisplay::moveAnimate(const Point &dest) {
    if (!inAnimation()) animation = std::make_shared<MoveAnimation>(this, getCenter(), dest);
}

void ComponentDisplay::swapAnimate(std::shared_ptr<ComponentDisplay>  other) {
    moveAnimate(other->getCenter());
    other->moveAnimate(getCenter());
}

void ComponentDisplay::popAnimate() {
    if (!inAnimation()) animation = std::make_shared<PopAnimation>(this);
}