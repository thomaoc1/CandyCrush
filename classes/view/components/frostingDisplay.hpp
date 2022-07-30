#ifndef FROSTING_HPP
#define FROSTING_HPP

#include "componentDisplay.hpp"
#include "../shapes/rectangle.hpp"
#include "../text/textDisplay.hpp"



class FrostingDisplay : public ComponentDisplay {
    int layers = 2;
    TextDisplay text;

public:
    FrostingDisplay(const Point &center, int layer) noexcept 
        : ComponentDisplay(std::make_shared<Rectangle>(center, Constants::FROSTING1, Constants::CELL_SIZE, FL_FLAT_BOX)),
                            layers{layer},
                            text{getCenter(), std::to_string(layers), FL_HELVETICA, static_cast<int>(getSize() / 1.5)} {}

    void explode() {--layers;}


    // DEBUG
    std::string type() const override {return layers==1 ? "F1" : "F2" ;}

};

#endif