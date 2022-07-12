#ifndef WRAPPED_DISPLAY_HPP
#define WRAPPED_DISPLAY_HPP

#include "componentDisplay.hpp"

class WrappedDisplay : public ComponentDisplay {
public:
    WrappedDisplay(Point center, int colour) : ComponentDisplay(center, colour) {}
    void draw() override;
    void drawShape() const override;
};

#endif