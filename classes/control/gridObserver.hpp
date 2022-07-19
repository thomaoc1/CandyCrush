#ifndef GRID_OBSERVER_HPP
#define GRID_OBSERVER_HPP

class GridDisplay;
class Grid;

#include "../view/gridDisplay.hpp"

#include <vector>
#include <iostream>


class GridObserver {
    GridDisplay * gridDisplay;
public:

    void setObserver(GridDisplay * display);

    void notifySwap(const Point &coord1, const Point &coord2) const;

    void notifyDropDown(const std::vector<Point> &/*drops*/) const {}
    void notifyDropLeft(const Point &/*coord*/) const {}
    void notifyDropRight(const Point &/*coord*/) const {}
    
    using CoordColour = std::pair<Point, int>;
    void notifyFill(const std::vector<CoordColour> &/*fills*/) const {}

    void notifyPop(const std::vector<Point> &/*pops*/) const {}
};

#endif