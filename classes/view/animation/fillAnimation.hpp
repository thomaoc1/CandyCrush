/**
 * @file fillAnimation.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is in charge of the graphical representation 
 *  of a filling animation.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef FILL_ANIMATION_HPP
#define FILL_ANIMATION_HPP

#include "animation.hpp"

class FillAnimation : public Animation {
    Fl_Color fl_colour;
    const double normalSize;
public:
    FillAnimation(ComponentDisplay * component) : Animation{component}, normalSize{component->getSize()} {}
    void draw() override;
private:
    int nextSize(int size) const;
};


#endif