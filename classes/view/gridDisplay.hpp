#ifndef GRID_DISPLAY_HPP
#define GRID_DISPLAY_HPP

#include "../model/grid.hpp"

#include <memory>

class GridDisplay {
    const std::shared_ptr< const Grid > grid;
public:
    GridDisplay(const std::shared_ptr< const Grid > grid) : grid{grid} {}
    void draw() const;
};

#endif