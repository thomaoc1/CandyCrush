#ifndef GRID_OBSERVER_HPP
#define GRID_OBSERVER_HPP

#include "subject.hpp"
#include <vector>

class GridObserver {
    void notifySwap() const;
    void notifyDropDown() const;
    void notifyDropLeft() const;
    void notifyDropRight() const;

};


#endif