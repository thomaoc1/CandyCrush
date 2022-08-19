#include "broadcast.hpp"


void BroadcastBox::draw() const {
    box.draw();
    text.draw(); 
    score.draw();
    swaps.draw();
    objective.draw();
}



void BroadcastBox::setObjective(int objType, int obj) {
    switch (objType) {
        case Constants::INGREDIENT:
            objective.setText("Cherries: " + std::to_string(obj));
            break;
        case Constants::FROSTINGS:
            objective.setText("Frostings: " + std::to_string(obj));
            break;
    }
}


void BroadcastBox::setObjective(int, int obj, Colour colour) {
    switch (colour) {
        case Colour::RED:
            objective.setText("Red Candies: " + std::to_string(obj));
            break;
        case Colour::BLUE:
            objective.setText("Blue Candies: " + std::to_string(obj));
            break;
        case Colour::GREEN:
            objective.setText("Green Candies: " + std::to_string(obj));
            break;
        case Colour::YELLOW:
            objective.setText("Yellow Candies: " + std::to_string(obj));
            break;
        case Colour::PURPLE:
            objective.setText("Purple Candies: " + std::to_string(obj));
            break;
        case Colour::ORANGE:
            objective.setText("Orange Candies: " + std::to_string(obj));
            break;   
        default:
            break; 
    }
}


