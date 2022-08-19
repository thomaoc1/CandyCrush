/**
 * @file moveAnimation.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of the graphical representation 
 *  of a moving animation.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef MOVE_ANIMATION_HPP
#define MOVE_ANIMATION_HPP

#include "../../common/point.hpp"
#include "animation.hpp"
#include "../components/componentDisplay.hpp"

#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>

class MoveAnimation  : public Animation {
    Point start;
    Point dest;
public:
    MoveAnimation(ComponentDisplay * component, const Point &start, const Point &dest) : Animation{component}, start{start}, dest{dest} {}
    void draw() override;
private:
    Point currentTranslation() const;
};

#endif