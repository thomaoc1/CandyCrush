#include "gridObserver.hpp"

void GridObserver::setObserver(GridDisplay * display) {gridDisplay = display;}

void GridObserver::notifySwap(const Point &c1, const Point &c2) const {
    std::cout << "Observer notifying display" << std::endl;
    // gridDisplay->componentSwap(c1, c2);
}