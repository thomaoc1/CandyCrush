/**
 * @file specialDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of 
 *  a SpecialBomb.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

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