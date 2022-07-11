#ifndef WRAPPED_DISPLAY_HPP
#define WRAPPED_DISPLAY_HPP

#include "colouredComponent.hpp"

class WrappedDisplay : public ColouredComponent {
public:
    WrappedDisplay(int colour) : ColouredComponent(colour) {}
    void draw(int y, int x) const override;
};

#endif