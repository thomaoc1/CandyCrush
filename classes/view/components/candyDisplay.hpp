/**
 * File : 
 *  candyDisplay.hpp
 *
 * Decription :
 *  Class responsible of displaying a specific gameComponent: "Candy".
 * 
 * Dependencies:
 *  componentDisplay.hpp
 * 
 * Authors:
 *  Thomas O'Cuilleanain,
 *  Marcus Chretien
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
    CandyDisplay(const Point &center, int colour) : ComponentDisplay{std::make_shared<Circle>(center, colour, Constants::CANDY_RADIUS)} {}
    CandyDisplay(const CandyDisplay &) = default;
    CandyDisplay(CandyDisplay &&) = default;
};

#endif