#ifndef STRIPED_DISPLAY_HPP
#define STRIPED_DISPLAY_HPP

#include "colouredComponent.hpp"

class StripedDisplay : public ColouredComponent {
public:
    StripedDisplay(int colour) : ColouredComponent(colour) {}
    void draw(int y, int x) const override;
};

#endif