#ifndef SWAPS_LEFT_DISPLAY_HPP 
#define SWAPS_LEFT_DISPLAY_HPP

#include "text.hpp"

#include "../../constants/constants.hpp"

class SwapsLeftDisplay : public Text {

public:
    SwapsLeftDisplay(const Point &center, int size, int swaps=-1)
        : Text{center, "Sawps left: " + std::to_string(swaps), FL_HELVETICA, size} {}
    SwapsLeftDisplay() = default;
    SwapsLeftDisplay(const SwapsLeftDisplay &) = default;
    SwapsLeftDisplay(SwapsLeftDisplay &&) = default;

    void setText(const std::string &message) override {text = "Swaps left: " + message;}
    void setText(std::string &&message) override {text = "Swaps left: " + message;}
    void draw() const override;
};

#endif