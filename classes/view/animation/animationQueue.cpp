#include "animationQueue.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


void AnimationQueue::enqueueSwap(const CoordPair &swap) {
    queue.push(AnimationType::Swap);
    swaps.push(swap);
}


void AnimationQueue::enqueueDrop(const std::vector<Point> &drop, Beneath direction) {
    switch (direction) {
        case Beneath::LEFT:
            queue.push(AnimationType::DropLeft);
            break;
        case Beneath::CENTER:
            queue.push(AnimationType::DropDown);
            break;
        case Beneath::RIGHT:
            queue.push(AnimationType::DropRight);
            break;
    }
    drops.push(drop);
}


void AnimationQueue::enqueuePop(const std::vector<Point> &pop) {
    queue.push(AnimationType::Pop);
    pops.push(pop);
}


void AnimationQueue::enqueueFill(const std::vector<CoordComponent> &fill) {
    queue.push(AnimationType::Fill);
    fills.push(fill);
}

AnimationType AnimationQueue::nextAnimation() {
    AnimationType ret = queue.front();
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
