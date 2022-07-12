#ifndef WRAPPED_DISPLAY_HPP
#define WRAPPED_DISPLAY_HPP

#include "colouredComponent.hpp"

class WrappedDisplay : public ColouredComponent {
public:
    WrappedDisplay(Point center, int colour) : ColouredComponent(center, colour) {}
    void draw() override;
    void drawShape() const override;
};

#endif