#ifndef ANIMATION_QUEUE_HPP 
#define ANIMATION_QUEUE_HPP

#include <queue>
#include "../../shared/point.hpp"
#include "../../constants/constants.hpp"

class AnimationQueue {
    using CoordColour = std::pair< Point, int >;
    using CoordPair = std::pair< Point, Point >;
    enum animations{Pop, Fill, DropDown, DropLeft, DropRight, Swap};

    std::queue< CoordPair > swaps;
    std::queue< std::vector<Point> > drops;
    std::queue< std::vector<Point> > pops;
    std::queue< std::vector<CoordColour> > fills;
    std::queue<int> queue;
public:
    AnimationQueue() = default;
    AnimationQueue(const AnimationQueue &) = default;
    AnimationQueue(AnimationQueue &&) = default;
    
    void clear() {queue = {}; swaps = {}; drops = {}; pops = {}; fills = {};}

    void enqueueSwap(const CoordPair &swap);
    void enqueueDrop(const std::vector<Point> &drops, int direction);
    void enqueuePop(const std::vector<Point> &pop);
    void enqueueFill(const std::vector<CoordColour> &fill);

    CoordPair nextSwap();
    std::vector<Point> nextDrop();
    std::vector<Point> nextPop();
    std::vector<CoordColour> nextFill();

    int size() const {return queue.size();}
    int nextAnimation();
};

#endif