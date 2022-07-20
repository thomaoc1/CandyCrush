#ifndef WRAPPED_DISPLAY_HPP
#define WRAPPED_DISPLAY_HPP

#include "componentDisplay.hpp"

class WrappedDisplay : public ComponentDisplay {
public:
    WrappedDisplay(Point center, int colour) : ComponentDisplay(center, Constants::CANDY_RADIUS, colour) {}
    void drawShape() const override;
};

#endif