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


void BroadcastBox::setObjective(int, int obj, int colour) {
    switch (colour) {
        case Constants::RED:
            objective.setText("Red Candies: " + std::to_string(obj));
            break;
        case Constants::BLUE:
            objective.setText("Blue Candies: " + std::to_string(obj));
            break;
        case Constants::GREEN:
            objective.setText("Green Candies: " + std::to_string(obj));
            break;
        case Constants::YELLOW:
            objective.setText("Yellow Candies: " + std::to_string(obj));
            break;
        case Constants::PURPLE:
            objective.setText("Purple Candies: " + std::to_string(obj));
            break;
        case Constants::ORANGE:
            objective.setText("Orange Candies: " + std::to_string(obj));
            break;    
    }
}


