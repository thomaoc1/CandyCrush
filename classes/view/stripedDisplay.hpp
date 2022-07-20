#ifndef STRIPED_DISPLAY_HPP
#define STRIPED_DISPLAY_HPP

#include "componentDisplay.hpp"

class StripedDisplay : public ComponentDisplay {
public:
    StripedDisplay(Point center, int colour) : ComponentDisplay(center, Constants::CANDY_RADIUS, colour) {}
    void drawShape() const override;
};

#endif