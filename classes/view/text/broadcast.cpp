#include "broadcast.hpp"


void BroadcastBox::draw() const {
    box.draw();
    text.draw(); 
    score.draw();
    swaps.draw();
    objective.draw();
}