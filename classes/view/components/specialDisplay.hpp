#ifndef SPECIAL_DISPLAY_HPP
#define SPECIAL_DISPLAY_HPP

#include "bombDisplay.hpp"

class SpecialDisplay : public BombDisplay {
public:
    SpecialDisplay(const Point &center) : BombDisplay(center, Colour::DARK_RED, "Sp") {}
    SpecialDisplay(const SpecialDisplay &) = default;
    SpecialDisplay(SpecialDisplay &&) = default;
};


#endif