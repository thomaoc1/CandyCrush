#ifndef EVENTS_HPP
#define EVENTS_HPP

#include "../point.hpp"

#include <vector>


class Events {
    typedef std::pair< Point, Point > PointPair; 
    std::vector<PointPair> moves;
};


#endif