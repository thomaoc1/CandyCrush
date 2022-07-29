#ifndef SPECIAL_DISPLAY_HPP
#define SPECIAL_DISPLAY_HPP

#include "bombDisplay.hpp"

class SpecialDisplay : public BombDisplay {
public:
    SpecialDisplay(const Point &center) : BombDisplay(center, Constants::SPECIAL_BOMB, "Sp") {}
    SpecialDisplay(const SpecialDisplay &) = default;
    SpecialDisplay(SpecialDisplay &&) = default;
};


#endif