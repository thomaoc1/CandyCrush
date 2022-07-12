#ifndef STRIPED_DISPLAY_HPP
#define STRIPED_DISPLAY_HPP

#include "colouredComponent.hpp"

class StripedDisplay : public ColouredComponent {
public:
    StripedDisplay(Point center, int colour) : ColouredComponent(center, colour) {}
    void draw() override;
    void drawShape() const override;
};

#endif