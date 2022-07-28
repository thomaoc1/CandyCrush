#ifndef BOMB_DISPLAY_HPP
#define BOMB_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"
#include "../text/textDisplay.hpp"

class BombDisplay : public ComponentDisplay {
    TextDisplay text;
public:
    BombDisplay(const Point &center, int colour, const std::string &type)
        : ComponentDisplay{std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)},
            text{getCenter(), type, FL_HELVETICA, static_cast<int>(getSize() / 1.5)} {};

    virtual void drawShape() const override;
    virtual void setCenter(const Point &dest) override;
    virtual void setSize(int newSize) override;
};

#endif