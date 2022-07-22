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

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class CandyDisplay : public ComponentDisplay {
public:
    CandyDisplay(Point center, int colour) : ComponentDisplay(center, Constants::CANDY_RADIUS, colour) {}
    void drawShape() const override;
};

#endif