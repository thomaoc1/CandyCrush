/**
 * @file candyDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation of 
 *  a Candy.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef CANDY_DISPLAY_HPP
#define CANDY_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/circle.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CandyDisplay : public ComponentDisplay {
public:
    CandyDisplay(const Point &center, Colour colour) : ComponentDisplay{std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)} {}
    CandyDisplay(const CandyDisplay &) = default;
    CandyDisplay(CandyDisplay &&) = default;
};

#endif