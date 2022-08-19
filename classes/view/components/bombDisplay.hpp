#ifndef BOMB_DISPLAY_HPP
#define BOMB_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"
#include "../text/text.hpp"

class BombDisplay : public ComponentDisplay {
    Text text;
public:
    BombDisplay(const Point &center, Colour colour, const std::string &type)
        : ComponentDisplay{std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)},
            text{getCenter(), type, FL_HELVETICA, static_cast<int>(getSize() / 1.5)} {};

    virtual void drawShape() const override;
    virtual void setCenter(const Point &dest) override;
    virtual void setSize(double newSize) override;
};

#endif