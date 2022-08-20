/**
 * @file frostingDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of 
 *  a Frosting.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef FROSTING_DISPLAY_HPP
#define FROSTING_DISPLAY_HPP

#include "componentDisplay.hpp"
#include "../shapes/rectangle.hpp"
#include "../text/componentText.hpp"

class FrostingDisplay : public ComponentDisplay {
    int layers;
    ComponentText text;

public:
    FrostingDisplay(const Point &center, int layer) noexcept 
        : ComponentDisplay(std::make_shared<Rectangle>(center, Colour::CYAN, Constants::CELL_SIZE, FL_FLAT_BOX)),
                            layers{layer},
                            text{getCenter(), std::to_string(layers), FL_HELVETICA, static_cast<int>(getSize() / 1.5)} {}

    void drawShape() const override; 
    void setSize(double newSize) override;

};

#endif