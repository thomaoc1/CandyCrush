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


void AnimationQueue::enqueueDrop(const std::vector<Point> &drop, Beneath direction) {
    switch (direction) {
        case Beneath::LEFT:
            queue.push(animations::DropLeft);
            break;
        case Beneath::CENTER:
            queue.push(animations::DropDown);
            break;
        case Beneath::RIGHT:
            queue.push(animations::DropRight);
            break;
    }
    drops.push(drop);
}


void AnimationQueue::enqueuePop(const std::vector<Point> &pop) {
    queue.push(animations::Pop);
    pops.push(pop);
}


void AnimationQueue::enqueueFill(const std::vector<CoordComponent> &fill) {
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

std::vector<AnimationQueue::CoordComponent> AnimationQueue::nextFill() { 
    std::vector<CoordComponent> ret = std::move(fills.front());
    fills.pop();
    return ret;
}
