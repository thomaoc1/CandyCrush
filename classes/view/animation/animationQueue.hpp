#ifndef ANIMATION_QUEUE_HPP 
#define ANIMATION_QUEUE_HPP

#include <queue>
#include "../../shared/point.hpp"
#include "../../common/constants.hpp"
#include "../../common/componentType.hpp"

class AnimationQueue {
    using CoordComponent = std::pair< Point, ComponentType >;
    using CoordPair = std::pair< Point, Point >;
    enum animations{Pop, Fill, DropDown, DropLeft, DropRight, Swap};

    std::queue< CoordPair > swaps;
    std::queue< std::vector<Point> > drops;
    std::queue< std::vector<Point> > pops;
    std::queue< std::vector<CoordComponent> > fills;
    std::queue<int> queue;
public:
    AnimationQueue() = default;
    AnimationQueue(const AnimationQueue &) = default;
    AnimationQueue(AnimationQueue &&) = default;
    
    void clear() {queue = {}; swaps = {}; drops = {}; pops = {}; fills = {};}

    void enqueueSwap(const CoordPair &swap);
    void enqueueDrop(const std::vector<Point> &drops, Beneath direction);
    void enqueuePop(const std::vector<Point> &pop);
    void enqueueFill(const std::vector<CoordComponent> &fill);

    CoordPair nextSwap();
    std::vector<Point> nextDrop();
    std::vector<Point> nextPop();
    std::vector<CoordComponent> nextFill();

    int size() const {return queue.size();}
    int nextAnimation();
};

#endif