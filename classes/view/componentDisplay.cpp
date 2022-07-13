#include "componentDisplay.hpp"


ComponentDisplay::ComponentDisplay(Point center, int colour = Constants::NONE) : center{center} {
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
    // First animation is still going
    if (animationStatus()) animations.front()->draw();
    else if (animations.size() > 1) {
        animations.pop();
        animations.front()->draw();
    }
    else if (animations.size() > 0) animations.pop();
    else drawShape();
}


bool ComponentDisplay::animationStatus() const {return animations.size() > 0 && !animations.front()->over();} 


bool ComponentDisplay::inAnimation() const {return animations.size() > 0;} /*return animationStatus() || animations.size() > 1;*/


void ComponentDisplay::moveAnimate(const Point &dest) {
    // gives center at time of animation
    Point previousDest = getCenter();
    if (inAnimation()) previousDest = animations.back()->finalLoc();
    animations.emplace(std::make_shared<MoveAnimation>(this, previousDest, dest));
}

void ComponentDisplay::swapAnimate(std::shared_ptr<ComponentDisplay>  other) {
    moveAnimate(other->getCenter());
    other->moveAnimate(getCenter());
}

void ComponentDisplay::popAnimate() {
    
}