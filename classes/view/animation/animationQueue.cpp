#include "animationQueue.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


void AnimationQueue::enqueueSwap(const CoordPair &swap) {
    queue.push(animations::Swap);
    swaps.push(swap);
}


void AnimationQueue::enqueueDrop(const std::vector<Point> &drop, int direction) {
    switch (direction) {
        case Constants::LEFT:
            queue.push(animations::DropLeft);
            break;
        case Constants::CENTER:
            queue.push(animations::DropDown);
            break;
        case Constants::RIGHT:
            queue.push(animations::DropRight);
            break;
    }
    drops.push(drop);
}


void AnimationQueue::enqueuePop(const std::vector<Point> &pop) {
    queue.push(animations::Pop);
    pops.push(pop);
}


void AnimationQueue::enqueueFill(const std::vector<CoordColour> &fill) {
    queue.push(animations::Fill);
    fills.push(fill);
}

int AnimationQueue::nextAnimation() {
    int ret = queue.front();
    queue.pop();
    return ret;
}

AnimationQueue::CoordPair AnimationQueue::nextSwap() {
    CoordPair ret = std::move(swaps.front());
    swaps.pop();
    return ret;
}

std::vector<Point> AnimationQueue::nextDrop() {
    std::vector<Point> ret = std::move(drops.front());
    drops.pop();
    return ret;
}

std::vector<Point> AnimationQueue::nextPop() {
    std::vector<Point> ret = std::move(pops.front());
    pops.pop();
    return ret;
}

std::vector<AnimationQueue::CoordColour> AnimationQueue::nextFill() { 
    std::vector<CoordColour> ret = std::move(fills.front());
    fills.pop();
    return ret;
}
