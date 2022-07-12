#include "cellDisplay.hpp"

void CellDisplay::draw(int animation) {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, frameColour);
    if (!occupied) return;
    if (currentAnimation && currentAnimation->animationOver()) currentAnimation = nullptr;
    if (!currentAnimation && animation != Constants::NO_ANIMATION) currentAnimation = std::make_shared<DropAnimation>(this);
    else occupied->draw(row, col);
}

void CellDisplay::drawNoAnimation() {
    fl_draw_box(FL_BORDER_FRAME, Constants::INTER_CELL * col + Constants::GAME_WINDOW_Xi,
                    Constants::INTER_CELL * row + Constants::GAME_WINDOW_Yi, Constants::INTER_CELL,
                    Constants::INTER_CELL, frameColour);
    if (occupied) occupied->draw(row, col);
}