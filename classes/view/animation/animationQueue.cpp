#include "animationQueue.hpp"


/*-------------------------------------------------------------------------------------------*
 *                                                                                           *
 *                                       Public Methods                                      *
 *                                                                                           *
 --------------------------------------------------------------------------------------------*/


/**
 * @brief Queues a swap
 * 
 * @param swap 
 */
void AnimationQueue::enqueueSwap(const CoordPair &swap) {
    queue.push(AnimationType::Swap);
    swaps.push(swap);
}


/**
 * @brief Queues a drop
 * 
 * @param drop 
 * @param direction 
 */
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


/**
 * @brief Queues a pop
 * 
 * @param pop 
 */
void AnimationQueue::enqueuePop(const std::vector<Point> &pop) {
    queue.push(AnimationType::Pop);
    pops.push(pop);
}


/**
 * @brief Queues a fill
 * 
 * @param fill 
 */
void AnimationQueue::enqueueFill(const std::vector<CoordComponent> &fill) {
    queue.push(AnimationType::Fill);
    fills.push(fill);
}


/**
 * @brief Returns the next animation and pops it from the queue.
 * 
 * @return AnimationType 
 */
AnimationType AnimationQueue::nextAnimation() {
    AnimationType ret = queue.front();
    queue.pop();
    return ret;
}


/**
 * @brief Returns next swap and pops it from the swap queue
 * 
 * @return AnimationQueue::CoordPair 
 */
AnimationQueue::CoordPair AnimationQueue::nextSwap() {
    CoordPair ret = std::move(swaps.front());
    swaps.pop();
    return ret;
}


/**
 * @brief Returns next drop and pops it from the drop queue
 * 
 * @return std::vector<Point> 
 */
std::vector<Point> AnimationQueue::nextDrop() {
    std::vector<Point> ret = std::move(drops.front());
    drops.pop();
    return ret;
}


/**
 * @brief Returns next set of pops and pops it from the pop queue
 * 
 * @return std::vector<Point> 
 */
std::vector<Point> AnimationQueue::nextPop() {
    std::vector<Point> ret = std::move(pops.front());
    pops.pop();
    return ret;
}


/**
 * @brief Returns next set of fills and pops it from the fill queue
 * 
 * @return std::vector<AnimationQueue::CoordComponent> 
 */
std::vector<AnimationQueue::CoordComponent> AnimationQueue::nextFill() { 
    std::vector<CoordComponent> ret = std::move(fills.front());
    fills.pop();
    return ret;
}
