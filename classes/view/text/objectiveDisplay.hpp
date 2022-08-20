/**
 * @file objectiveDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is responsible for the graphical representation of the 
 * Objective text.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef OBJECTIVE_DISPLAY_HPP 
#define OBJECTIVE_DISPLAY_HPP

#include "text.hpp"

#include "../../common/constants.hpp"

class ObjectiveDisplay : public Text {
public:
    ObjectiveDisplay(const Point &center, int size, int nbObjective=0)
        : Text{center, "Reds to Pop: " + std::to_string(nbObjective), FL_HELVETICA, size} {}
    ObjectiveDisplay() = default;
    ObjectiveDisplay(const ObjectiveDisplay &) = default;
    ObjectiveDisplay(ObjectiveDisplay &&) = default;

    void setText(const std::string &message) override {text = message;}
    void setText(std::string &&message) override {text = message;}
    void draw() const override;
};

#endif