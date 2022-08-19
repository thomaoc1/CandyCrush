/**
 * @file swapsLeftDisplay.hpp
 * @author Thomas O'Cuilleanain
 * @author Marcus Chretien
 * 
 * @brief Class which is reponsible for the graphical representation of the amount of
 * swaps left text.
 * 
 * @version 0.1
 * @date 2022-08-19
 * 
 */

#ifndef SWAPS_LEFT_DISPLAY_HPP 
#define SWAPS_LEFT_DISPLAY_HPP

#include "text.hpp"

#include "../../common/constants.hpp"

class SwapsLeftDisplay : public Text {
public:
    SwapsLeftDisplay(const Point &center, int size, int swaps=0)
        : Text{center, "Swaps left: " + std::to_string(swaps), FL_HELVETICA, size} {}
    SwapsLeftDisplay() = default;
    SwapsLeftDisplay(const SwapsLeftDisplay &) = default;
    SwapsLeftDisplay(SwapsLeftDisplay &&) = default;

    void setText(const std::string &message) override {text = "Swaps left: " + message;}
    void setText(std::string &&message) override {text = "Swaps left: " + message;}
    void draw() const override;
};

#endif